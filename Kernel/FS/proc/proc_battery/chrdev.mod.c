#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3b8f800d, "module_layout" },
	{ 0x93c6e498, "mod_timer" },
	{ 0x6067a146, "memcpy" },
	{ 0xdcb5671d, "strlen" },
	{ 0x9edbecae, "snprintf" },
	{ 0x6e24745f, "add_timer" },
	{ 0x7d11c268, "jiffies" },
	{ 0x872e6354, "init_timer_key" },
	{ 0xe54c5f49, "create_proc_entry" },
	{ 0x32587fbc, "proc_mkdir" },
	{ 0x82e4cfa2, "device_create" },
	{ 0xc832776b, "__class_create" },
	{ 0x8bf87169, "__bzero" },
	{ 0x105e2727, "__tracepoint_kmalloc" },
	{ 0xd00d9142, "kmem_cache_alloc" },
	{ 0xb5f3ea02, "kmalloc_caches" },
	{ 0xbbee9241, "cdev_add" },
	{ 0xb5600dc4, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xea147363, "printk" },
	{ 0x49b5ac4e, "remove_proc_entry" },
	{ 0x37a0cba, "kfree" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xae7b99f0, "class_destroy" },
	{ 0xa1ff3d2f, "device_destroy" },
	{ 0x1ec1b79, "cdev_del" },
	{ 0xe612aa25, "del_timer" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

