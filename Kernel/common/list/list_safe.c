#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>

struct student{
    char name[50];
    int num;
    struct list_head list;
};

struct student *studentp;
struct student *tmp_studentp;
struct list_head student_list;
struct list_head *pos;

static int __init  list_init(void)
{
   int i = 0;

   INIT_LIST_HEAD(&student_list);

   studentp = kmalloc(sizeof(struct student) * 5, GFP_KERNEL);
   if (!studentp)
   {
       printk("<0>NOMEEM\n");
       return -ENOMEM;
   }
   memset(studentp, 0, sizeof(struct student) * 5);

   for (i = 0; i < 5; i++)
   {
       sprintf(studentp[i].name, "student %d", i + 1);
       studentp[i].num = i + 1;
       list_add(&studentp[i].list, &student_list);
   }

   list_for_each_entry_reverse(tmp_studentp, &student_list, list)
   {
       printk("<0>student %d name: %s\n", tmp_studentp->num, tmp_studentp->name);
   }
   
   return 0;
}


static void __exit list_exit(void)
{
    struct list_head *node;

    list_for_each_safe(pos, node, &student_list)
    {
        tmp_studentp = list_entry(pos, struct student, list);
        list_del(&(tmp_studentp->list));
        printk("<0>student %d name: %s is being delete.\n", tmp_studentp->num, tmp_studentp->name);
    }
    kfree(studentp);
}

module_init(list_init);
module_exit(list_exit);
