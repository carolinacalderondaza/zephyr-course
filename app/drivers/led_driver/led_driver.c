#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <errno.h>
#include "led_driver.h"

#define DT_DRV_COMPAT led_driver

LOG_MODULE_REGISTER(led_driver, LOG_LEVEL_INF);

struct led_driver_data {
    int led_state;
};

static const struct gpio_dt_spec led =
   // GPIO_DT_SPEC_GET(DT_NODELABEL(blue_led), gpios);   //Manejo GPIO con blue_led
    GPIO_DT_SPEC_INST_GET(0 , gpios);

static int sample_fetch_my_impl(const struct device *dev, enum sensor_channel chan)
{
    LOG_INF("Hello From Sample Fetch, channel %d", chan);
    int ret = gpio_pin_set_dt(&led, 1);
    //LOG_INF("gpio_pin_set ON ret = %d", ret);
    return ret;
}

static int channel_get_my_impl(const struct device *dev, enum sensor_channel chan, struct sensor_value *val){
	
    LOG_INF("Hello From Channel Get, channel %d", chan);
        
    int ret = gpio_pin_set_dt(&led, 0);

    struct led_driver_data *data = dev->data;
    val->val1 = data->led_state;
    val->val2 = 0;

    return ret;

}


static struct led_driver_data led_data;

int led_driver_set_state(const struct device *dev, int state)
{
    struct led_driver_data *data = dev->data;
    data->led_state = state;
    LOG_INF("led_state = %d", data->led_state);

    return 0;
}

struct led_driver_api {
    struct sensor_driver_api sensor_api;
    int (*set_led_state)(const struct device *dev, int state);
};


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

//DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);
DEVICE_DT_INST_DEFINE(0, init, NULL, &led_data, NULL, POST_KERNEL, 80, &api_iomico_lecture);


