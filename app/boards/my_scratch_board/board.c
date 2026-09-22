#include<zephyr/init.h>
#include<zephyr/kernel.h>
#include <zephyr/sys/printk.h>


static int my_scratch_board_init(void) {
/* Some function to run before boot */

    printk("My Scratch Board Initialized!\n");
    return 0;

}

SYS_INIT(my_scratch_board_init, PRE_KERNEL_1, 0);
