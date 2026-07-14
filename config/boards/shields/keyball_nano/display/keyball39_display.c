#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

#include <zmk/display.h>
#include <zmk/event-manager.h>
#include <zmk/events/layer.h>
#include <zmk/events/position-state-changed.h>
#include <zmk/events/keycode-state-changed.h>
#include <zmk/keymap.h>

LOG_MODULE_REGISTER(keyball39_display, LOG_LEVEL_INF);

static const struct device *display_dev;
static int current_layer = 0;

static void draw_status_screen(void)
{
    if (!display_dev) {
        return;
    }

    struct display_buffer_descriptor buf_desc;
    buf_desc.width = 128;
    buf_desc.height = 32;
    buf_desc.pitch = 128;
    buf_desc.buf_size = 128 * 32 / 8;

    uint8_t framebuffer[128 * 32 / 8];
    memset(framebuffer, 0, sizeof(framebuffer));

    if (current_layer == 1) {
        cfb_framebuffer_init(display_dev, framebuffer, 128, 32);
        cfb_print(display_dev, framebuffer, 0, 0, "MOUSE MODE", 10);
        cfb_print(display_dev, framebuffer, 0, 12, "ACTIVE", 6);
        cfb_framebuffer_finalize(display_dev, framebuffer);
        return;
    }

    cfb_framebuffer_init(display_dev, framebuffer, 128, 32);
    cfb_print(display_dev, framebuffer, 0, 0, "MAIN", 4);
    cfb_print(display_dev, framebuffer, 0, 12, "LAYER", 5);
    cfb_framebuffer_finalize(display_dev, framebuffer);
}

static void keyball39_display_work_handler(struct k_work *work)
{
    ARG_UNUSED(work);
    draw_status_screen();
}

K_WORK_DEFINE(keyball39_display_work, keyball39_display_work_handler);

static void layer_state_changed(const struct zmk_event_header *eh)
{
    struct zmk_layer_state_changed *event = CONTAINER_OF(eh, struct zmk_layer_state_changed, header);
    current_layer = event->layer;
    k_work_submit(&keyball39_display_work);
}

ZMK_EVENT_CONSUMER(layer_state_changed) {
    return zmk_layer_state_changed_from_state(event);
}

static int keyball39_display_init(void)
{
    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        LOG_ERR("display device not ready");
        return -ENODEV;
    }

    k_work_submit(&keyball39_display_work);
    return 0;
}

SYS_INIT(keyball39_display_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
