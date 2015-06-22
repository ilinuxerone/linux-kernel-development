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
	{ 0x41086e, "module_layout" },
	{ 0x6980fe91, "param_get_int" },
	{ 0xff964b25, "param_set_int" },
	{ 0xffc7c184, "__init_waitqueue_head" },
	{ 0x105e2727, "__tracepoint_kmalloc" },
	{ 0x8fde5204, "slab_buffer_size" },
	{ 0xfc822e6e, "kmem_cache_alloc_notrace" },
	{ 0xc288f8ce, "malloc_sizes" },
	{ 0x40c497a1, "cdev_add" },
	{ 0xf28b622f, "cdev_init" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x2da418b5, "copy_to_user" },
	{ 0x9ccb2622, "finish_wait" },
	{ 0x33d92f9a, "prepare_to_wait" },
	{ 0x4292364c, "schedule" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x7d0bea0b, "per_cpu__current_task" },
	{ 0x642e54ac, "__wake_up" },
	{ 0xf2a644fb, "copy_from_user" },
	{ 0xb72397d5, "printk" },
	{ 0x8f05adee, "remap_pfn_range" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x37a0cba, "kfree" },
	{ 0xbef9fe65, "cdev_del" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "8C2A2741C9AC2F8D2C1BDA1");