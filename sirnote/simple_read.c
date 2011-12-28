#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
static char *name =  "foo";
static int major;

static int foo_open(struct inode *inode , struct file *filep)
{
	printk("opened the device which have the major number %d\n",major);
	return 0;
}

static int foo_read(struct file *filep,char *buf,size_t count, loff_t *foff)
{
	static char msg[] = "hello, world\n";
	int data_len = strlen(msg);
	int curr_off = *foff,remaining;
		
	if(curr_off >= data_len) return 0;
	remaining = data_len - curr_off;
	
	if(count <= remaining) {
 		if(copy_to_user(buf,msg+curr_off,count))
			return -EFAULT;
		*foff = *foff + count;
		return count;
	} else { 
		if(copy_to_user(buf,msg+curr_off,remaining)) 
			return -EFAULT;
		*foff = *foff + remaining;
		return remaining;
	}
}

static struct file_operations fops = {
	open : foo_open,
	read : foo_read,
};
	
int init_module(void)
{
	major = register_chrdev(0,name,&fops);
	printk("registered the char device with major number %d \n",major);
	return 0;
}

void cleanup_module(void)
{
	printk("deregistering module \n");
	unregister_chrdev(major,name);
}
