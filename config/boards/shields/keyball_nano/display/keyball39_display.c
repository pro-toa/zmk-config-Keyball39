#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(keyball39_display, LOG_LEVEL_INF);

static const struct device *display_dev;

static void draw_status_screen(void)
{
    if (!display_dev || !device_is_ready(display_dev)) {
        return;
    }

    display_blanking_off(display_dev);
    display_write(display_dev, 0, 0, 16, "MOUSE ACTIVE", 12);
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
