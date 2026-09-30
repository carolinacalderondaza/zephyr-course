#include <zephyr/shell/shell.h>

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


