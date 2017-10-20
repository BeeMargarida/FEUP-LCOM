#include "rtc.h"


static unsigned char bcd_to_bin(unsigned char bcd)
{
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void rtc_disable_int(){
	asm("cli");
}
void rtc_enable_int(){
	asm("sti");
}

Date *getDateOnly(){

	unsigned long result;

	Date *d;
	d = (Date *) malloc(sizeof(Date));

	rtc_disable_int();

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return;
		if (sys_inb(RTC_RW_REG, &result))
			return;
	}
	sys_outb(RTC_ADDR_REG, DAY);
	sys_inb(RTC_RW_REG, &d->day);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return;
		if (sys_inb(RTC_RW_REG, &result))
			return;
	}
	sys_outb(RTC_ADDR_REG, MONTH);
	sys_inb(RTC_RW_REG, &d->month);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return;
		if (sys_inb(RTC_RW_REG, &result))
			return;
	}
	sys_outb(RTC_ADDR_REG, YEAR);
	sys_inb(RTC_RW_REG, &d->year);

	d->day = bcd_to_bin(d->day);
	d->month = bcd_to_bin(d->month);
	d->year = bcd_to_bin(d->year);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return;
		if (sys_inb(RTC_RW_REG, &result))
			return;
	}
	sys_outb(RTC_ADDR_REG, HOUR);
	sys_inb(RTC_RW_REG, &d->hours);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return;
		if (sys_inb(RTC_RW_REG, &result))
			return;
	}
	sys_outb(RTC_ADDR_REG, MINU);
	sys_inb(RTC_RW_REG, &d->minutes);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return;
		if (sys_inb(RTC_RW_REG, &result))
			return;
	}
	sys_outb(RTC_ADDR_REG, SEC);
	sys_inb(RTC_RW_REG, &d->seconds);

	d->hours = bcd_to_bin(d->hours);
	d->minutes = bcd_to_bin(d->minutes);
	d->seconds = bcd_to_bin(d->seconds);

	rtc_enable_int();
	return d; //se estiver tudo bem
}

int getDate(){

	unsigned long result;

	Date *d;
	d = (Date *) malloc(sizeof(Date));

	rtc_disable_int();

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, DAY);
	sys_inb(RTC_RW_REG, &d->day);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, MONTH);
	sys_inb(RTC_RW_REG, &d->month);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, YEAR);
	sys_inb(RTC_RW_REG, &d->year);

	d->day = bcd_to_bin(d->day);
	d->month = bcd_to_bin(d->month);
	d->year = bcd_to_bin(d->year);

	rtc_enable_int();
	show_date(d);
	return 0; //se estiver tudo bem
}
int getDateandHours(){

	unsigned long result;

	Date *d;
	d = (Date *) malloc(sizeof(Date));

	rtc_disable_int();

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, DAY);
	sys_inb(RTC_RW_REG, &d->day);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, MONTH);
	sys_inb(RTC_RW_REG, &d->month);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, YEAR);
	sys_inb(RTC_RW_REG, &d->year);

	d->day = bcd_to_bin(d->day);
	d->month = bcd_to_bin(d->month);
	d->year = bcd_to_bin(d->year);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, HOUR);
	sys_inb(RTC_RW_REG, &d->hours);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, MINU);
	sys_inb(RTC_RW_REG, &d->minutes);

	while(result & 0x80)
	{
		if (sys_outb(RTC_ADDR_REG, REGA))
			return 1;
		if (sys_inb(RTC_RW_REG, &result))
			return 1;
	}
	sys_outb(RTC_ADDR_REG, SEC);
	sys_inb(RTC_RW_REG, &d->seconds);

	d->hours = bcd_to_bin(d->hours);
	d->minutes = bcd_to_bin(d->minutes);
	d->seconds = bcd_to_bin(d->seconds);

	rtc_enable_int();
	show_date_and_hours(d);
	return 0; //se estiver tudo bem
}

void rtc_set_alarm(){
	unsigned long result;

	rtc_disable_int();

	sys_outb(RTC_ADDR_REG,REGB);
	sys_inb(RTC_RW_REG,&result);

	result = result & ~BIT(PIE);
	result = result & ~BIT(AIE);
	result = result & ~BIT(UIE);


	sys_outb(RTC_ADDR_REG,REGB);
	sys_outb(RTC_RW_REG,result);
	Date *d = getDateOnly();

	unsigned long hour = d->hours;
	unsigned long minutes = d->minutes;
	unsigned long seconds = d->seconds + 2;
	sys_outb(RTC_RW_REG, SECA); //seconds
	sys_outb(RTC_RW_REG, seconds);
	sys_outb(RTC_RW_REG, MINUA); //minutes
	sys_outb(RTC_RW_REG, minutes);
	sys_outb(RTC_RW_REG, HOURA);//hours
	sys_outb(RTC_RW_REG, hour);

	rtc_enable_int();
}

int rtc_handler(){
	unsigned long result;
	sys_outb(RTC_ADDR_REG,REGC);
	sys_inb(RTC_RW_REG,&result);
	return 0;
}
