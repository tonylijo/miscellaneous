#include<stdio.h>

char *strcpy_1(char *dst,char *src)
{
	if(*src) {
		*dst = *src;
		strcpy_1(++dst,++src);
	} else {
		*dst = 0;
	}
	return dst;
}

char *strcat_1(char *dst,char *src)
{
	static flag ; 
	if(!flag) {
		while(*dst++);
		dst--;
	}
	flag = 1;
	if(*src) {
		*dst = *src;
		strcat_1(++dst,++src);
	} else {
		*dst = 0;
	}
	return dst;
}

void swap(char *a,char *b)
{
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void strrev_1(char *src)
{
	static int count;
	static char *last;
	int temp = count++;
	if(*src != 0) {
		strrev_1(++src);
	} else {
		last = --src;
		return;
	}
       	if(src > &last[-temp]) {
		printf("%d\n",temp);
		swap(src,&last[-temp]);
	}
}
int main()
{
	char str1[] = "tony";
	char str2[] = "lijo";
	char dummy[100];
	strcpy_1(dummy,str1);
	printf("%s\n",dummy);
	strcat_1(dummy,str1);
	printf("%s\n",dummy);
	strrev_1(dummy);
	printf("%s\n",dummy);
}
