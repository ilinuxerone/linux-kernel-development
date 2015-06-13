#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>


struct student {
    char name[50];
    int num;
    struct list_head list;
};


struct student *studentp;
struct student *tmp_studentp;
struct list_head student_list;
struct list_head *pos;
struct list_head pop;

static int __init list_init(void)
{
    int i = 0;
    INIT_LIST_HEAD(&student_list);

    studentp = kmalloc(sizeof(struct student) * 5, GFP_KERNEL);
    if (!studentp)
    {
        printk("<0> NOMEM\n");
        return -ENOMEM;
    } 
    memset(studentp, 0, sizeof(struct student) * 5);

    for (i = 0; i < 5; i++)
    {
       sprintf(studentp[i].name, "student %d", i + 1);
       studentp[i].num=i + 1;
       list_add(&studentp[i].list, &student_list);
    }

    //traverse list
    list_for_each(pos, &student_list)
    {
        tmp_studentp = list_entry(pos, struct student, list);
        printk("<0> student%d name : %s\n", tmp_studentp->num, tmp_studentp->name);
    }

    //traverse list reverse
    list_for_each_entry_reverse(tmp_studentp, &student_list, list)
    {
        printk("<0>student %d name : %s\n", tmp_studentp->num, tmp_studentp->name);
    }
    return 0;
}

static void __exit list_exit(void)
{
    int i = 0;
 	
     /* 实验：将for换成list_for_each来遍历删除结点，观察要发生的现象，并考虑解决办法 */   
    /*
    for (i = 0; i < 5; i++)
    {
	printk("<0> %s", studentp[i].name);
        list_del(&studentp[i].list);

    }
    kfree(studentp);
    */
    list_for_each(pos, &student_list)
    {
	tmp_studentp = list_entry(pos, struct student, list);
     	pop = tmp_studentp->list;
	list_del(&(tmp_studentp->list));
	printk("<0>Delete pstudent[%d], name is %s\n", studentp[tmp_studentp->num-1].num,studentp[tmp_studentp->num - 1].name );
//	pos = &pop;	
    }
}


module_init(list_init);
module_exit(list_exit);
