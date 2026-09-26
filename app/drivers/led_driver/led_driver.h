#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int led_driver_set_state(const struct device *dev, int state);

#ifdef __cplusplus
}
#endif

#endif
