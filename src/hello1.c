#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Prokhorenko Artem, IO-23");
MODULE_DESCRIPTION("Hello1 module exporting print_hello()");

struct time_list {
    struct list_head list;
    ktime_t start;
    ktime_t end;
};

static LIST_HEAD(time_list_head);

void print_hello(int count) {
    struct time_list *entry;
    int i;

    for (i = 0; i < count; i++) {
        entry = kmalloc(sizeof(*entry), GFP_KERNEL);
        if (!entry)
            return;

        entry->start = ktime_get();
        pr_info("Hello, world! %d/%d\n", i + 1, count);
        entry->end = ktime_get();

        list_add_tail(&entry->list, &time_list_head);
    }
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void) {
    pr_info("Hello1 module loaded.\n");
    return 0;
}

static void __exit hello1_exit(void) {
    struct time_list *entry, *tmp;

    pr_info("Hello1 module unloaded. Times logged:\n");

    list_for_each_entry_safe(entry, tmp, &time_list_head, list) {
        pr_info("Time spent: %lld ns\n", ktime_to_ns(entry->end) - ktime_to_ns(entry->start));
        list_del(&entry->list);
        kfree(entry);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);
