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
	{ 0x2f2a965d, "netlink_unicast" },
	{ 0xbacdc1df, "nla_put" },
	{ 0xd0d8621b, "strlen" },
	{ 0x2bc95bd4, "memset" },
	{ 0x7e0913d, "skb_put" },
	{ 0x669fad8a, "__alloc_skb" },
	{ 0xadabf25, "genl_register_ops" },
	{ 0xdca0e950, "genl_register_family" },
	{ 0x49439411, "genl_unregister_family" },
	{ 0x872741d6, "genl_unregister_ops" },
	{ 0xb72397d5, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EC979B2EDE0DAC19E3AC483");
