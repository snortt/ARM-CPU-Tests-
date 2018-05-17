
//#include "mloader.h"
//#include "libc.h"
//#include "clock.h"

//void *memcpy (void *dst0, const void *src0, size_t len)
//{	char *dst=(char *)dst0;
//	char *src=(char *)src0;
//	while(len--) *dst++=*src++;
//	return dst0;
//}
	
//size_t strlen(const char *s)
//{	size_t i=0;
//	while(*s++!=0) i++;
//	return i;
//}

//char *strcpy(char *dest, const char *src)
//{
//	return (char *)memcpy(dest,src,strlen(src)+1);
//}

/*  Space is really tight right now and these are not being used
int memcmp(const void *s1, const void *s2, size_t n)
{	char *ps1=(char *)s1;
	char *ps2=(char *)s2;

	while(n--) 
	{	if(*ps1!=*ps2)
			return *ps2-*ps1;
		ps1++; 
		ps2++;
	};
	return 0;
}

int strcmp(const char *s1, const char *s2)
{	return memcmp(s1, s2, strlen(s1)+1);
}

int strncmp(const char *s1, const char *s2, size_t n)
{	size_t len=n;
	if(strlen(s1)<len)
		len=strlen(s1);
	return memcmp(s1, s2, len);
}
*/

//void *memset(void *s, int c, size_t n)
//{	char *buf=(char *)s;
//	while(n--) *buf++=c;
//	return s;
//}

/* Only guarantees that the delay will be more than us micro-seconds */
//int udelay(int us)
//{	//uint32_t cycles=(us*(MERLIN_ARM_CLK_HZ/1000000))/3;	/* divided by 3 because about 3 instructions per loop */
//	//while(cycles--);
//	return 0;
//}

//int raise (int sig)
//{	puts("FATAL signal ");
//	putint(sig);
//	puts("\n");
//	BUG();
//	/*return 0;*/
//}
