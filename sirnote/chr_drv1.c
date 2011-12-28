#include<linux/module.h>
#include<linux/fs.h>
static char *name = "foo";
static int major;
static int foo_open(struct inode *inode,struct file *filp)
{
	printk("major %d , minor %d \n",MAJOR(inode->i_rdev),MINOR(inode->i_rdev));
	/*
	*perform what ever action that a 
	*physical hardware has to do.
	*hear
	*/

	printk("offset %d \n",(int)filp->f_pos);
	printk("filep->f_op->open = %x \n",(unsigned int)filp->f_op->open);
	printk("address of foo_open = %x \n",(unsigned int)foo_open);
	return 0;
}

static int foo_read(struct file *filp,char *buf,size_t count,loff_t *offp)
{
	printk("&filp->f_pos=%x\n",(unsigned int)&filp->f_pos);
	printk("offp=%x\n",(unsigned int)offp);
	return 0;
}

static int foo_write(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	/*as of now dummy*/
	return 0;
}


static struct file_operations fops = {
	open : foo_open,
	read : foo_read,
	write : foo_write,
};

int init_module(void)
{
	printk("initailizing the module \n");
	major = register_chrdev(0,name,&fops);
	printk("registered charecter device with major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("cleaning up module .......\n");
	unregister_chrdev(major,name);
}
