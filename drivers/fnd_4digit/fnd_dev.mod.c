#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0x3d82956c, "gpio_to_desc" },
	{ 0xd1948ef, "gpiod_set_raw_value" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x504b3a4, "gpiod_direction_output_raw" },
	{ 0x27dbbade, "kthread_create_on_node" },
	{ 0x28b147b9, "wake_up_process" },
	{ 0x3407c0e, "misc_register" },
	{ 0x92997ed8, "_printk" },
	{ 0xc03d0d37, "kthread_stop" },
	{ 0xfe990052, "gpio_free" },
	{ 0x1c090c0b, "misc_deregister" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xc358aaf8, "snprintf" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x5f754e5a, "memset" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa400a71f, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "480825C71DF040117647EDE");
