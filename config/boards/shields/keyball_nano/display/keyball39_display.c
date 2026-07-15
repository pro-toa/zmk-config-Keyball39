#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>
#include <zmk/event-manager.h>
#include <zmk/events/layer.h>
#include <zmk/keymap.h>

LOG_MODULE_REGISTER(keyball39_display, LOG_LEVEL_INF);

static const struct device *display_dev;
static int current_layer = 0;

static void draw_status_screen(void)
{
    if (!display_dev || !device_is_ready(display_dev)) {
        return;
    }

    display_blanking_off(display_dev);

    if (current_layer == 1) {
        LOG_INF("MOUSE layer active");
    } else {
        LOG_INF("Layer: %d", current_layer);
    }
}

static void layer_state_changed(const struct zmk_event_header *eh)
{
    struct zmk_layer_state_changed *event = CONTAINER_OF(eh, struct zmk_layer_state_changed, header);
    current_layer = event->layer;
    draw_status_screen();
}

ZMK_EVENT_CONSUMER(layer_state_changed) {
    return zmk_layer_state_changed_from_state(event);
}

static int keyball39_display_init(void)
{
    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!display_dev || !device_is_ready(display_dev)) {
        LOG_ERR("display device not ready");
        return -ENODEV;
    }

    draw_status_screen();
    return 0;
}

SYS_INIT(keyball39_display_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
