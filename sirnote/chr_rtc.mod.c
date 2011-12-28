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
	{ 0xc90df394, "module_layout" },
	{ 0xf09c7f68, "__wake_up" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xbad7d2da, "interruptible_sleep_on" },
	{ 0xbb377d25, "__register_chrdev" },
	{ 0x50eedeb8, "printk" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

