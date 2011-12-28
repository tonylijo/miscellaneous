#define ADDRESS_REG 0x70
#define DATA_REG 0x71
#define ADDRESS_REG_MASK 0xe0
#define STATUS_A 0x0a
#define STATUS_B 0x0b
#define STATUS_C 0x0c
#define SECOND 0x00

#define SA_INTERRUPT    0x20000000
#define RTC_PIE_ON 0x10 /* Enable Periodic Interrupt*/
#define RTC_IRQP_SET 0x20 /*Set periodic interrupt rate*/
#define RTC_PIE_OFF 0x30 /*Disable Periodic Interrupt*/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/interrupt.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<asm/io.h>

#define RTC_IRQ 8
#define MODULE_NAME "rtc"
static int major;

DECLARE_WAIT_QUEUE_HEAD(rtc_queue);
unsigned char rtc_inb(unsigned char addr)
{
	unsigned char i,j;
	i = inb(ADDRESS_REG);
	i = i & ADDRESS_REG_MASK;
	i = i | addr;
	outb(i,ADDRESS_REG);
	j = inb(DATA_REG);
	return j;
}

void rtc_outb(unsigned char data,unsigned char addr)
{
	unsigned char i;
	i = inb(ADDRESS_REG);
	/* Clear lower 5 bits*/
	i = i & ADDRESS_REG_MASK;
	i = i | addr;
	outb(i,ADDRESS_REG);
	outb(data,DATA_REG);
}

void enable_periodic_interrupt(void)
{
	unsigned char c;
	c = rtc_inb(STATUS_B);
	/*set Periodic Interrupt enable bit */
	c = c | (1 << 6);
	rtc_outb(c,STATUS_B);
	rtc_inb(STATUS_C);
}

void disable_periodic_interrupt(void)
{
	unsigned char c;
	c = rtc_inb(STATUS_B);
	/*set Periodic Interrupt enable bit*/
	c = c & ~(1 << 6);
	rtc_outb(c,STATUS_B);
}

int set_periodic_interrupt_rate(unsigned char rate)
{
	unsigned char c;
	if((rate < 3) && (rate > 15) ) return -EINVAL;
	printk("setting rate %d\n",rate);
	c = rtc_inb(STATUS_A);
	c = c & ~0xf;
	c = c | rate;
	rtc_outb(c,STATUS_A);
	printk("new rate = %d \n",rtc_inb(STATUS_A) & 0xf);
	return 0;
}

void rtc_int_handler(int irq,void *devid,struct pt_regs *regs)
{
	wake_up_interruptible(&rtc_queue);
	rtc_inb(STATUS_C);
}

int rtc_open(struct inode *inode ,struct file *filp)
{
	int result;
	result = request_irq(RTC_IRQ,
	rtc_int_handler,SA_INTERRUPT,MODULE_NAME,0);
	if(result < 0) {
		printk("unable to get IRQ %d \n",RTC_IRQ);
		return result;
	}
	return result;
}

int rtc_close(struct inode *inode,struct file *filp)
{
	free_irq(RTC_IRQ,0);
	return 0;
}

int rtc_ioctl(struct file *filp,
	unsigned int cmd,unsigned long val)
{
	int result = 0;
	switch(cmd) {
		case RTC_PIE_ON:
		enable_periodic_interrupt();
		break;
		case RTC_PIE_OFF:
		disable_periodic_interrupt();
		break;
		case RTC_IRQP_SET:
		result = set_periodic_interrupt_rate(val);
		break;
	}	
	return result;
}

size_t rtc_read(struct file *filp,char *buf,
		size_t len,loff_t *offp)
{
	interruptible_sleep_on(&rtc_queue);
	return 0;
}

struct file_operations fops = {
	open: rtc_open,
	release: rtc_close,
	unlocked_ioctl: rtc_ioctl,
	read: rtc_read,
};
	
int rtc_init_module(void)
{
	major = register_chrdev(0,MODULE_NAME,&fops);
	if(major < 0) {
		printk("Error register char device \n");
		return major;
	}
	printk("major = %d\n",major);
	return 0;
}

void rtc_cleanup(void)
{
	unregister_chrdev(major,MODULE_NAME);
}

module_init(rtc_init_module);
module_exit(rtc_cleanup);
