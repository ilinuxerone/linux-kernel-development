#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define procfs_dir_name  "proctest"
struct proc_dir_entry *filep;
struct proc_dir_entry *dirp;
char msg[255] = "hello world!\n";

int my_read_proc(char *page, char  **stat, off_t off, int count, int *peof, void *data)
{
    int len = strlen(msg);

    //ret = sprintf(buffer, "hello World!\n");
    if (off >= len)
    {
        return 0;
    }
    if (count > len - off)
        count = len - off;
    memcpy(page + off, msg + off, count);
    return off + count;
}

int my_write_proc(struct file *filep, char *buffer, unsigned long count, void *data)
{
    unsigned long count2 = count;

    if (count2 >= sizeof(msg))
        count2 = sizeof(msg) - 1;
    if (copy_from_user(msg, buffer, count2))
        return -EFAULT;
    
    return count;
}

static int __init proc_init(void)
{
    dirp = proc_mkdir("mydir3", NULL);
    if (!dirp)
    {
        remove_proc_entry("/proc/mydir3", NULL);
        printk("<0>Can't create /proc/mydir3 directory\n");
        return -1;
    }

    filep = create_proc_entry(procfs_dir_name, 0644, dirp);
    if (!filep)
    {
        remove_proc_entry("proctest", dirp);
        printk("<0>ERROR: Couldn't create /proc/%s/%s\n", dirp->name, procfs_dir_name);
        return -ENOMEM;
    }    

   filep->read_proc = my_read_proc;
   filep->write_proc = my_write_proc;
   filep->size = 37;
   printk("<0>/proc/mydir3/proctest created\n");
   return 0;
}

static void __exit proc_exit(void)
{
    remove_proc_entry(procfs_dir_name, dirp);
    //remove_proc_entry("/proc/mydir3", NULL);
    remove_proc_entry("mydir3", NULL);
    printk("<0>/proc/mydir3/proctest removed\n" );
}


module_init(proc_init);
module_exit(proc_exit);
