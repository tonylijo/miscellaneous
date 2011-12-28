#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include"foo.h"
static char *name = "foo";
static int major;

static long foo_ioctl(struct file *filep,unsigned int cmd,
	unsigned long arg)
{
	printk("recieved ioctl number %x \n",cmd);
	return 0;
}

static struct file_operations fops = {
	unlocked_ioctl: foo_ioctl,
};

int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("registered device with the major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("cleaning up module .....\n");
	unregister_chrdev(major,name);

}
