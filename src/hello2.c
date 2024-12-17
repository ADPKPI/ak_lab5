#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Prokhorenko Artem, IO-23");
MODULE_DESCRIPTION("Hello2 module using print_hello() from hello1");

static int count = 3;
module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of times to call print_hello");

static int __init hello2_init(void) {
    pr_info("Hello2 module loaded. Calling print_hello()...\n");

    if (count > 10) {
        pr_err("Error: count exceeds the maximum allowed value.\n");
        return -EINVAL;
    } else if (count == 0 || (count >= 5 && count <= 10)) {
        pr_warn("Warning: count is 0 or between 5 and 10.\n");
    }

    print_hello(count);
    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Hello2 module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
