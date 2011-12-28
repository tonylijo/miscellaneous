#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

static char *name = "foo";
static int major;
static int end;

static int foo_open(struct inode *inode , struct file *filep)
{
	printk("opened the device with major number %d \n",major);
	return 0;
}

static int foo_read(struct file *filep,char *buf,size_t count,
		loff_t *f_pos) 
{
	static int nseconds = 2;
	char c = 'A';
	
	end = jiffies + nseconds*HZ;
	
	while(jiffies < end) ;
	copy_to_user(buf,&c,1);
	return 1;
}

static struct file_operations fops = {
	open : foo_open,
	read : foo_read,
};

int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("initialising module \n");
	printk("registered device with major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("cleaning up the module......\n");
	unregister_chrdev(major,name);
	printk("claned the module ......\n");
}
	
