#include<linux/module.h>
#include<linux/fs.h>

static char *name = "foo";
static int major;

static int foo_open(struct inode *inode,struct file *filp)
{
	return 0;
}

static int foo_close(struct inode *inode,struct file *filp)
{
	printk("closing device .....\n");
	return 0;
}

static struct file_operations fops = {
	open : foo_open,
	release : foo_close,
};

int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("got the major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("cleaning up the module ... \n");
	unregister_chrdev(major,name);
}
