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
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x953d56cb, "module_put" },
	{ 0x37a0cba, "kfree" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xd111ca5b, "kmalloc_caches" },
	{ 0x2ec2b47f, "kmalloc_trace" },
	{ 0x5f754e5a, "memset" },
	{ 0x3d82956c, "gpio_to_desc" },
	{ 0xe7f7d433, "gpiod_to_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0xdc911bb9, "try_module_get" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x28118cb6, "__get_user_1" },
	{ 0xd1948ef, "gpiod_set_raw_value" },
	{ 0x800473f, "__cond_resched" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x1000e51, "schedule" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0x49970de8, "finish_wait" },
	{ 0xbb72d4fe, "__put_user_1" },
	{ 0xfd0f592, "mutex_trylock" },
	{ 0x9618ede0, "mutex_unlock" },
	{ 0xde4bf88b, "__mutex_init" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x504b3a4, "gpiod_direction_output_raw" },
	{ 0xe498c05c, "gpiod_direction_input" },
	{ 0x1fe34ff9, "__register_chrdev" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0x637493f3, "__wake_up" },
	{ 0x6d7fba3, "param_ops_charp" },
	{ 0x99409edb, "param_ops_int" },
	{ 0xa400a71f, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7283AFD59CFBADD846A5F5D");
