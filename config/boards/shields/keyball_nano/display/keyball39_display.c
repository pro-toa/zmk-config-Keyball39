#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/display/cfb.h>
#include <zephyr/logging/log.h>
#include <string.h>

LOG_MODULE_REGISTER(keyball39_display, LOG_LEVEL_INF);

static const struct device *display_dev;

static void draw_status_screen(void)
{
    if (!display_dev || !device_is_ready(display_dev)) {
        return;
    }

    static struct cfb_framebuffer framebuffer;
    uint8_t buffer[128 * 32 / 8];
    memset(buffer, 0, sizeof(buffer));

    framebuffer.buf = buffer;
    framebuffer.width = 128;
    framebuffer.height = 32;
    framebuffer.pitch = 128;
    framebuffer.pixels_per_byte = 1;

    cfb_framebuffer_init(display_dev, &framebuffer);
    cfb_print(display_dev, &framebuffer, 0, 0, "MOUSE MODE", 10);
    cfb_print(display_dev, &framebuffer, 0, 12, "ACTIVE", 6);
    cfb_framebuffer_finalize(display_dev, &framebuffer);
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
