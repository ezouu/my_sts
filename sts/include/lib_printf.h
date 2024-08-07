#include <stdarg.h>
int printf(const char *templat,...);
int xvsprintf(char *outbuf,const char *templat,va_list marker);
int xsprintf(char *buf,const char *templat,...);
int xprintf(const char *templat,...);

extern int (*xprinthook)(const char *);
int xvprintf(const char *template,va_list marker);


//#define printf xprintf
#define sprintf xsprintf
#define vsprintf xvsprintf
#define vprintf xvprintf
