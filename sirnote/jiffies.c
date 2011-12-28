#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/sched.h>

static char *name = "foo";
static int major;

DECLARE_WAIT_QUEUE_HEAD(foo_queue);

static int foo_read(struct file *filep,char *buf,size_t count,loff_t *f_pos)
{
	static int nseconds = 2;
	char c = 'A';
	interruptible_sleep_on_timeout(&foo_queue,nseconds*HZ);
	copy_to_user(buf,&c,1);
	return 1;
}

static struct file_operations fops = {
	open : NULL,
	read : foo_read,
};

int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("registered device with major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("cleaning up the module ......\n");
	unregister_chrdev(major,name);
}
