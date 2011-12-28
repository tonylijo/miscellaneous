static int end;

static int foo_read(struct file *filp,char *buf,size_t count,loff_t *f_pos)
{
	static int nseconds = 2;
	char c = 'A';
	
	end = jiffies + nseconds*HZ;
	while(jiffies < end);
	
	copy_to_user(buf,&c,1);
	return 1;
}
