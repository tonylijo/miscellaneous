#include<linux/module.h>
#include<linux/sched.h>
#include<linux/fs.h>
#include<linux/binfmts.h>
static int mybinfmt(struct linux_binprm *bprm, struct pt_regs *regs) 
{
	printk(KERN_ALERT"hello not printable characters !\n");
	return -ENOEXEC;
}
static struct linux_binfmt ghost_format = {
	
	.module = THIS_MODULE,
	.load_binary = mybinfmt,
};
int init_module(void)
{
	printk("loading ghost \n");
	return register_binfmt(&ghost_format);
}
void cleanup_module(void)
{
	printk(KERN_ALERT"cleaning up the module");
	unregister_binfmt(&ghost_format);
}

