#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/sched.h>
DECLARE_WAIT_QUEUE_HEAD(foo_queue);

static char *name = "foo";
static int major;

static int foo_open(struct inode *inode,struct file *filep)
{
	if(filep->f_flags == O_RDONLY) {
		printk("reader going to sleep \n");
		interruptible_sleep_on(&foo_queue);
	} else if(filep->f_flags == O_WRONLY) {
		printk("writer waking up readers \n");
		wake_up_interruptible(&foo_queue);
	}
	return 0;
}

static struct file_operations fops = {
	open: foo_open,
};

int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("registered the char dev with the major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("unregistering the module \n");
	unregister_chrdev(major,name);
}
