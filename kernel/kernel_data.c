#include<linux/module.h>
#include<linux/sched.h>

int init_module(void)
{
	printk("hello\n");
	printk("name = %s \n",current->comm);
	printk("pid = %d \n",current->pid);
	return 0;
}

void cleanup_module(void)
{
	printk("world\n");
}
