#include <zephyr/shell/shell.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdlib.h>
#include <errno.h>
#include "led_driver.h"

/* Shell para info cmd */

static int cmd_info_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver =
        DEVICE_DT_GET(DT_NODELABEL(led_driver0));

    shell_print(sh, "Device: %s", driver->name);
    shell_print(sh, "Ready: %s",
                device_is_ready(driver) ? "yes" : "no");

    return 0;
}


/* Shell para fetch cmd */

static int cmd_fetch_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver =
        DEVICE_DT_GET(DT_NODELABEL(led_driver0));

    int ret = sensor_sample_fetch(driver);

    shell_print(sh, "Sample fetch returned: %d", ret);

    return ret;
}

/* Shell para read cmd */

static int cmd_read_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver =
        DEVICE_DT_GET(DT_NODELABEL(led_driver0));

    struct sensor_value val;

    int ret = sensor_channel_get(
        driver,
        SENSOR_CHAN_AMBIENT_TEMP,
        &val
    );

    shell_print(sh, "Channel get returned: %d", ret);
    shell_print(sh, "Value: %d.%06d", val.val1, val.val2);

    return ret;
}

/* Shell para read set */

static int cmd_set_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver =
        DEVICE_DT_GET(DT_NODELABEL(led_driver0));

    int value = atoi(argv[1]);

    if (value < 0 || value > 100) {
        shell_error(sh, "Value must be between 0 and 100");
        return -EINVAL;
    }

    led_driver_set_state(driver, value);

    shell_print(sh, "LED state set to %d", value);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd,
    [0] = SHELL_CMD_ARG(
        info,
        NULL,
        "Show sensor device information",
        cmd_info_handler,
        1,
        0
    ),
        [1] = SHELL_CMD_ARG(
        fetch,
        NULL,
        "Fetch a sensor sample",
        cmd_fetch_handler,
        1,
        0
    ),

        [2] = SHELL_CMD_ARG(
        read,
        NULL,
        "Read sensor value",
        cmd_read_handler,
        1,
        0
    ),

        [3] = SHELL_CMD_ARG(
        set,
        NULL,
        "Set LED state",
        cmd_set_handler,
        2,
        0
    ),

    [4] = SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor commands", NULL );


/* Shell para channel get cmd */

static int cmd_channel_get_handler(const struct shell *sh, int argc, char ** argv)
{
  shell_info(sh, "Hello from channel get handler");
  return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(led_driver_subcmd,
      [0]=SHELL_CMD_ARG(channel_get, NULL, "Get channel of my led_driver", cmd_channel_get_handler,1,0),
      [1]=SHELL_SUBCMD_SET_END,
);


SHELL_CMD_REGISTER(led_driver, &led_driver_subcmd, "Led driver set of commands", NULL);



