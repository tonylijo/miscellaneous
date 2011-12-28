#include<linux/module.h>
#include<linux/fs.h>

static struct file_operations fops = {
	open : NULL,
	read : NULL,
	write : NULL,
};

static char *name = "foo";
static int major ;

int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("Registered, got major = %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("cleaning up ....... \n");
	unregister_chrdev(major,name);
}
