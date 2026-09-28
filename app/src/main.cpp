#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include "../drivers/led_driver/led_driver.h"


/* The devicetree node identifier for the "led0" alias. */
/* First it will look to app.overlay */

#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
        int i=0;
	void test () {
		const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(led_driver0));
		struct sensor_value val;
		auto ret = sensor_sample_fetch(driver);
		LOG_INF("Sample fetch ret %d", ret);
		led_driver_set_state(driver, i);
		i++;
		
		k_msleep(500);
		
		ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
		LOG_INF("Channel ret %d", ret);
		led_driver_set_state(driver, i);
		i++;
		
		k_msleep(500);
	}
}

int main(void)
{
   
   /* Blue led with Zephir driver*/
   
   
   bool led_state = true;
    if (!gpio_is_ready_dt(&led)) return 0;
    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    
    

    while (1) {
    
    test();
    
     /* Blue led with Zephir driver*/
      
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);   
    }   
    
   
    return 0;
}
