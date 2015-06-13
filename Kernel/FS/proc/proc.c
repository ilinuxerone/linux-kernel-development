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

    /*
    * int offset = 0;
    * char *message = "hello world: ";
    * strcpy(page + offset, message);
    * offset += strlen(message);
    * memcpy(page + offset, data, strlen(data));
    * offset += strlen(data);
    * page[offset] = '\n';
    * offset += 1;
    * return offset;
    */
    
    return off + count;
}

int my_write_proc(struct file *filep, char *buffer, unsigned long count, void *data)
{
    unsigned long count2 = count;

    if (count2 >= sizeof(msg))
        count2 = sizeof(msg) - 1;
    if (copy_from_user(msg, buffer, count2))
        return -EFAULT;

    /*
    *  char *kernel_buf;
    *  if (count < 0 || count > PAGE_SIZE)
    *      return -EFAULT;
    *
    *  kernel_buf = kmalloc(count + 1, GFP_KERNEL);
    *  if (copy_from_user(kernel_buf, buffer, count)){
    *      kfree(kernel_buf);
    *      return -EFAULT;   
    *  }
    *
    *  kernel_buf[count] = '\0';
    *  printk("write_first received data: %s\n", kernel_buf);
    *  printk("first filename %s\n", file->f_dentry->d_iname);
    *  printk("write_first data %s\n", (char *)data);
    *
    */
    
    return count;
}

static int __init proc_init(void)
{
    /*Create a directory*/
    dirp = proc_mkdir("mydir3", NULL);
    if (!dirp)
    {
        return -ENOMEM;
    }

    /*Create a file*/
    filep = create_proc_entry(procfs_dir_name, 0644, dirp);
    if (!filep)
    {
        remove_proc_entry("/proc/mydir3", NULL);
        printk("<0>ERROR: Couldn't create /proc/%s/%s\n", dirp->name, procfs_dir_name);
        return -ENOMEM;
    }    


   filep->data = kmalloc(strlen("filep private data"), GFP_KERNEL);
   strcpy(filep->data, "filep private data");
   filep->read_proc = my_read_proc;
   filep->write_proc = my_write_proc;
   printk("<0>/proc/mydir3/proctest created\n");
   return 0;
}

static void __exit proc_exit(void)
{
    kfree(filep->data);
    remove_proc_entry(procfs_dir_name, dirp);
    //remove_proc_entry("/proc/mydir3", NULL);
    remove_proc_entry("mydir3", NULL);
    printk("<0>/proc/mydir3/proctest removed\n" );
}


module_init(proc_init);
module_exit(proc_exit);
