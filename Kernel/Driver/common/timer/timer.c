#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <asm/uaccess.h>


struct timer_list timer;
static long count;

void timer_func(unsigned long arg)
{
    printk("<0> timer expired and arg is %u count is %d\n", arg, count++);
    mod_timer(&timer, jiffies + 5 * HZ);
}

static int __init timer_init(void)
{
    init_timer(&timer);    
    timer.expires = jiffies + 5 * HZ;
    timer.function = timer_func;
    timer.data = 5;
    add_timer(&timer);
    return 0;
}


static void __exit timer_exit(void)
{
    del_timer(&timer);
}


module_init(timer_init);
module_exit(timer_exit);
