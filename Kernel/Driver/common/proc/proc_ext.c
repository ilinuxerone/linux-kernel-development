#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

static struct proc_dir_entry *dirp;
static struct proc_dir_entry *filep;
static char msg[512]="hello world!\n";

static int my_file_read(struct file *file, char *data, size_t len, loff_t *off)
{
    if (*off > 0)
        return 0;
    if (copy_to_user(data, msg, strlen(msg)))
        return -EFAULT;
    *off += strlen(msg);
    return strlen(msg);   
}

static int my_file_write(struct file *file, const char *data, size_t len, loff_t *off)
{
    if (copy_from_user(msg, (void*)data, len))
        return -EFAULT;
    msg[len] = '\n'; 
    return len;
}

static struct file_operations  my_file_ops = {
    .read = my_file_read,
    .write = my_file_write,
};

static int __init proc_init(void)
{
    dirp = proc_mkdir("mydir2", NULL);
    if (!dirp)
    {
        printk("<0>ERROR: Couldn't create /proc/mydir2");
        return -EFAULT;
    }

    filep = create_proc_entry("proctest", 0666, dirp);
    if (!filep)
    {
        remove_proc_entry("/proc/mydir2", NULL);
        printk("<0>ERROR: Couldn't create /proc/mydir2/proctest");
        return -EFAULT;
    }

    filep->proc_fops = &my_file_ops;
    return 0;
}


static void __exit proc_exit(void)
{
    remove_proc_entry("proctest", dirp);
    remove_proc_entry("mydir2", NULL);
    printk("<0>/proc/mydir2/proctest removed\n" );
}

module_init(proc_init);
module_exit(proc_exit);
