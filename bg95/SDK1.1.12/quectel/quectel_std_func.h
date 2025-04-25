/******************************************************************************

                Q U E C T E L _ S T D _ F U N . H

******************************************************************************/
#ifndef __QUECTEL_STD_FUNC_H__
#define __QUECTEL_STD_FUNC_H__

char *quectel_itoa( int value, char *string,int radix);
long int quectel_strtol(const char *str, char **endptr, int base);
unsigned long int quectel_strtoul(const char *str, char **endptr, int base);

#endif /* __QUECTEL_STD_FUNC_H__ */



