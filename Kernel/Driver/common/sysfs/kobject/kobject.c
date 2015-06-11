#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhang zhihong");
MODULE_DESCRIPTION("kobject module");
MODULE_VERSION("1.0");

ssize_t kobj_show(struct kobject *kobj, struct attribute *attr, char *buf);
ssize_t kobj_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count);
void kobj_release(struct kobject *kobj);

struct  sysfs_ops  kobj_ops ={
	.show = kobj_show,
	.store = kobj_store,
};

struct attribute kobj_attr ={
	.name = "kobject_config",
	.mode = 0777,
};

struct attribute  *def_attrs[] ={
	&kobj_attr,
	NULL,
};

struct kobj_type  ktype ={
	.release = kobj_release,
	.default_attrs = def_attrs, 
	.sysfs_ops = &kobj_ops,
};

void kobj_release(struct kobject *kobj)
{
	printk("<0>kobj->name: %s released\n", kobj->name);	
}

ssize_t kobj_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	printk("<0>have show\n");
	printk("<0>attrname is %s\n", attr->name);
	sprintf(buf, "%s\n", attr->name);
	return strlen(buf) + 2;	
}

ssize_t kobj_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count)
{
	printk("<0>have store\n");
	printk("<0>write %s\n", buf);
	return count;
}

struct kobject  kobj;
static int __init  kobj_init(void)
{
	kobject_init_and_add(&kobj, &ktype, NULL, "kobject_test_module");
	printk("<0>kobject initialized success!");
}

static void __exit kobj_exit(void)
{
	kobject_del(&kobj);	
	printk("<0>kobject deleted!");
}


module_init(kobj_init);
module_exit(kobj_exit);