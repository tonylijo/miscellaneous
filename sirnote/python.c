#include<linux/module.h>
#include<linux/string.h>
#include<linux/stat.h>
#include<linux/slab.h>
#include<linux/binfmts.h>
#include<linux/init.h>
#include<linux/file.h>

int is_python_binary(struct linux_binprm *bprm)
{
	char py_magic[] = {209,242,13,10};
	int i;
	for(i = 0; i < 4; i++) 
		if(bprm->buf[i] != py_magic[i]) return 0;
	return 1;
}

static int load_py(struct linux_binprm *bprm,
		struct pt_regs *regs)
{
	printk("pybin load script invoked");
	return -ENOEXEC;
}

static struct linux_binfmt py_format = {
	NULL,
	THIS_MODULE,
	load_py,
	NULL,
	NULL,
	0,
};

int pybin_init_module(void)
{
	return register_binfmt(&py_format);
}

void pybin_cleanup(void)
{
	unregister_binfmt(&py_format);
	return ;
}

module_init(pybin_init_module);
module_exit(pybin_cleanup);
