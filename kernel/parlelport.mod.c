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
	{ 0xadf42bd5, "__request_region" },
	{ 0xb8aa2342, "__check_region" },
	{ 0xbb377d25, "__register_chrdev" },
	{ 0x50eedeb8, "printk" },
	{ 0x9bce482f, "__release_region" },
	{ 0x59d8223a, "ioport_resource" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x2da418b5, "copy_to_user" },
	{ 0x33d169c9, "_copy_from_user" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

