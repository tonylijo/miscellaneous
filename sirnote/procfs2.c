#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>

#define PROCFS_MAX_SIZE 1024
#define PROCFS_NAME "bufferlk"

static struct proc_dir_entry *our_proc_file;
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;

int procfile_read(char *buffer,
		char **buffer_location,
		off_t offset,int buffer_length,
		int *eof,
		void *data)
{
	int ret;
	printk(KERN_INFO"procfile_read (/proc/%s) called\n",PROCFS_NAME);
	if(offset > 0) {
		ret = 0;
	} else {
		memcpy(buffer,procfs_buffer,procfs_buffer_size);
		ret = procfs_buffer_size;
	}

	return ret;
}

int procfile_write(struct file *file,const char *buffer,unsigned long count,
		void *data)
{
	procfs_buffer_size = count;
	if(procfs_buffer_size > PROCFS_MAX_SIZE) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}

	if(copy_from_user(procfs_buffer,buffer,procfs_buffer_size)) {
		return -EFAULT;
	}

	return procfs_buffer_size;
}

int init_module()
{
	our_proc_file = create_proc_entry(PROCFS_NAME,0644,NULL);
	if(our_proc_file == NULL) {
		remove_proc_entry(PROCFS_NAME,NULL);
		printk(KERN_ALERT"Error: could not initialize /proc/%s\n",
				PROCFS_NAME);
		return -ENOMEM;
	}

	our_proc_file->read_proc = procfile_read;
	our_proc_file->write_proc = procfile_write;
//	our_proc_file->owner = THIS_MODULE;
	our_proc_file->mode = S_IFREG | S_IRUGO;
	our_proc_file->uid = 0;
	our_proc_file->gid = 0;
	our_proc_file->size = 37;
	printk(KERN_INFO"/proc/%s created\n",PROCFS_NAME);
	return 0;
}


void cleanup_module()
{
	remove_proc_entry(PROCFS_NAME,NULL);
	printk(KERN_INFO"/proc/%s removed\n",PROCFS_NAME);
}
