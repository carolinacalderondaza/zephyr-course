#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <errno.h>

#define DT_DRV_COMPAT led_driver

LOG_MODULE_REGISTER(led_driver, LOG_LEVEL_INF);

static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(DT_NODELABEL(blue_led), gpios);
    

static int sample_fetch_my_impl(const struct device *dev, enum sensor_channel chan)
{
    LOG_INF("Hello From Sample Fetch, channel %d", chan);
    int ret = gpio_pin_set_dt(&led, 1);
    LOG_INF("gpio_pin_set ON ret = %d", ret);
    return ret;
}

static int channel_get_my_impl(const struct device *dev, enum sensor_channel chan, struct sensor_value *val){
	LOG_INF("Hello From Channel Get, channel %d", chan);
        
        int ret = gpio_pin_set_dt(&led, 0);
        LOG_INF("gpio_pin_set OFF ret = %d", ret);
        return ret;

}


static DEVICE_API(sensor, api_iomico_lecture) = {
        .sample_fetch = sample_fetch_my_impl,
	.channel_get = channel_get_my_impl,
};

// Init-fn
static int init(const struct device *dev){
	LOG_INF("Device Initialized!");

        if (!gpio_is_ready_dt(&led)) {
            LOG_ERR("LED GPIO is not ready");
            return -ENODEV;
        }

        int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

        LOG_INF("GPIO configure ret = %d", ret);

        return ret;

}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);
