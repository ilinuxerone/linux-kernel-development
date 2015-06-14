#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
//MODULE_LICENSE("DualBSD/GPL");

static __init int sysctl_init(void)
{
    int ret = 0;
    char cmdPath[]="/usr/bin/touch";
    char* cmdArgv[]={cmdPath,"/touchX.txt",NULL};
    char* cmdEnvp[]={"HOME=/",
"PATH=/sbin:/bin:/usr/bin",NULL};
    ret=call_usermodehelper(cmdPath,cmdArgv,cmdEnvp,UMH_WAIT_PROC);
    printk(KERN_DEBUG"testDriver1_initexec!Theret of call_usermodehelper is %d\n",ret);
    printk(KERN_DEBUG"testDriver1_initexec!Theprocess is \"%s\",sys_getpid is %d \n",current->comm,current->pid);

    return ret;
}


static __exit void sysctl_exit(void)
{
    int ret=0;
    char cmdPath[]="/bin/rm";
    char* cmdArgv[]={cmdPath,"/touchX.txt",NULL};
    char* cmdEnvp[]={"HOME=/",
"PATH=/sbin:/bin:/usr/bin",NULL};
    ret=call_usermodehelper(cmdPath,cmdArgv,cmdEnvp,UMH_WAIT_PROC);
    printk(KERN_DEBUG"testDriver1_exitexec!Theret of call_usermodehelper is %d\n",ret);
    printk(KERN_DEBUG"testDriver1_exitexec!Theprocess is \"%s\",pidis %d \n",current->comm,current->pid);
}

module_init(sysctl_init);
module_exit(sysctl_exit);
