#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/gfp.h>

char *buf_malloc = NULL;
char *buf_page = NULL;

int __init mem_alloc(void)
{
   printk("mem_alloc called!");

   buf_malloc = kmalloc(100, GFP_KERNEL);
   if (!buf_malloc)
   {
	printk(KERN_ERR "Kmalloc failed!\n");
    	return -ENOMEM;
   }
   memset(buf_malloc, 0, sizeof(buf_malloc));
   strcpy(buf_malloc, "---Kmalloc mem allocked finished!---"); 
   printk("<0>buf_malloc: %s\n", buf_malloc);

   buf_page = get_zeroed_page(GFP_KERNEL);
   if (NULL == buf_page)
   {
	printk(KERN_ERR "get_zeroed_page failed!\n");
	return -ENOMEM;
   }
   strcpy(buf_page, "----get_zeroed_page finished!---");
   printk("<0>buf_page: %s\n", buf_page);
   return 0;
}


void __exit mem_free(void)
{
    printk("mem_free called!");
    kfree(buf_malloc);
    free_page((unsigned long)buf_page);
}


module_init(mem_alloc);
module_exit(mem_free);
