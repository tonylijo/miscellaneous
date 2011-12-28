#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/sched.h>
#include<linux/interrupt.h>
#include<linux/kernel.h>
#include<linux/io.h>
#include<linux/signal.h>

#define SA_INTERRUPT    0x20000000
#define DATA_REG 0x71
#define ADDRESS_REG 0x70
#define ADDRESS_REG_MASK 0xe0
#define STATUS_A 0x0a
#define STATUS_B 0x0b
#define STATUS_C 0x0c
#define SECOND 0x00

#define RTC_IRQ 8
#define MODULE_NAME "rtc"

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
	i = i & ADDRESS_REG_MASK;
	i = i | addr;
	outb(i,ADDRESS_REG);
	outb(data,DATA_REG);
}

void enable_periodic_interrupt(void)
{
	unsigned char c;
	c = rtc_inb(STATUS_B);
	/*set periodic interrupt enable bit*/
	c = c | (1 << 6);
	rtc_outb(c,STATUS_B);
	rtc_inb(STATUS_C);
}

void disable_periodic_interrupt(void)
{
	unsigned char c;
	c = rtc_inb(STATUS_B);
	c = c & ~(1 << 6);
	rtc_outb(c,STATUS_B);
}

int set_periodic_interrupt_rate(unsigned char rate)
{
	unsigned char c;
	if((rate < 3) && (rate > 15)) return -EINVAL;
	printk("setting rate %d \n",rate);
	c = rtc_inb(STATUS_A);
	c = c & ~0x0f;
	c = c | rate;
	rtc_outb(c,STATUS_A);
	printk("new rate = %d \n",rtc_inb(STATUS_A) & 0xf);
	return 0;
}

void rtc_int_handler(int irq,void *devid,struct pt_regs *regs)
{
	printk("handler called \n");
	rtc_inb(STATUS_C);
}

int rtc_init_module(void)
{
	int result ;
	result = request_irq(RTC_IRQ,rtc_int_handler,
	SA_INTERRUPT,MODULE_NAME,0);
	
	if(result < 0) {
		printk("unable to get irq %d \n",RTC_IRQ);
		return result;
	}
	
	disable_periodic_interrupt();
	set_periodic_interrupt_rate(15);
	enable_periodic_interrupt();
	return result;
}

void rtc_cleanup_module(void)
{
	free_irq(RTC_IRQ,0);
}

module_init(rtc_init_module);
module_exit(rtc_cleanup_module);
	
