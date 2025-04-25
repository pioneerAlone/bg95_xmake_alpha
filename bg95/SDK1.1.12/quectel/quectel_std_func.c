/******************************************************************************

                Q U E C T E L _ S T D _ F U N C . C

******************************************************************************/
#include<stdlib.h>
#include<string.h>

/**************************************************************************
*                                 FUNCTION
***************************************************************************/
/*
@func
    quectel_itoa
    This function is used to convert an integer value to a string representation.
@brief
    [in]    value
            Value that needs to convert into string.
    [in]    string
            Pointer to the memory buffer where the converted string should be saved, make sure that the buffer has enough space.
    [in]    radix
            The integer format (hex(16), binary(2) or decimal(10)). 
*/
char *quectel_itoa( int value, char *string,int radix)
{  
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    unsigned unum = 0; 
    int i = 0;
    int j = 0;
    int k = 0; 

    if(string == NULL)
    {
        return string;
    }
    
    if(radix == 10 && value < 0) 
    { 
        unum = (unsigned) - value; 
        string[i++] = '-'; 
    } 
    else 
    {
        unum = (unsigned)value;
    }
    
    do  
    { 
        string[i++] = index[unum%(unsigned)radix]; 
        unum /= radix; 
    }while(unum); 
    
    string[i] = '\0'; 
    if(string[0] == '-')
    {
        k = 1;
    }
    else
    {
        k = 0;
    }

    for(j = k; j <= (i-k-1)/2.0; j++) 
    { 
        char temp = string[j]; 
        string[j] = string[i-j-1]; 
        string[i-j-1] = temp; 
    } 
    
    return string; 
} 

/*
@func
    quectel_strtol
    This function is used to convert string to long integer.
@brief
    [in]    nptr
            C-string containing the representation of an integral number.
    [in]    endptr
            Reference to an object of type char*, whose value is set by the function to the next character in str after the numerical value.
    [in]    base
            Numerical base (radix) that determines the valid characters and their interpretation.
*/
long int quectel_strtol(char *nptr, char **endptr, int base)
{
	char *temp_nptr = NULL;
	int sign_flag = 0;
	int err_flag = 0;
	long int val = 0;

	temp_nptr = nptr;

    if(temp_nptr == NULL)
    {
        return 0;
    }

    if(strlen(temp_nptr) == 0)
    {
        return 0;
    }
	
	while (*temp_nptr == ' ')  
	{
		temp_nptr++;
	}

	if (*temp_nptr == '-') 
	{
		sign_flag = 1;
		temp_nptr++;
	}
	else if (*temp_nptr == '+')
	{
		sign_flag = 0;
		temp_nptr++;
	}

	if((base == 0 || base == 16)
	&& (*temp_nptr == '0')
	&& (temp_nptr[1] == 'X' || temp_nptr[1] == 'x'))
	{
		temp_nptr += 2;
		base = 16;
	}

	if(base == 0)
	{
		base = (*temp_nptr == '0' ? 8 : 10);
		temp_nptr++;
	}

    switch(base)
    {
		case 2:
			if(!(*temp_nptr >= '0' && *temp_nptr <= '1'))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;
		
		case 8:
			if(!(*temp_nptr >= '0' && *temp_nptr <= '7'))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;
		
		case 10:
			if(!(*temp_nptr >= '0' && *temp_nptr <= '9'))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;

		case 16:
			if(!((*temp_nptr >= '0' && *temp_nptr <= '9') 
			|| (*temp_nptr >= 'a' && *temp_nptr <= 'f')
			|| (*temp_nptr >= 'A' && *temp_nptr <= 'F')))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;

		default:
			err_flag = 0;
		break;
	}

	if(err_flag == 1)
	{
		*endptr = temp_nptr;
		return 0;
	}
	else
	{
		val = strtol(temp_nptr, endptr, base);
		if(sign_flag)
		{
			val = -val;
		}
	}
	return val;
}


/*
@func
    quectel_strtoul
    This function is used to convert string to unsigned long integer.
@brief
    [in]    nptr
            C-string containing the representation of an integral number.
    [in]    endptr
            Reference to an object of type char*, whose value is set by the function to the next character in str after the numerical value.
    [in]    base
            Numerical base (radix) that determines the valid characters and their interpretation.
*/
unsigned long int quectel_strtoul(char *nptr, char **endptr, int base)
{
	char *temp_nptr = NULL;
	int err_flag = 0;
	unsigned long val = 0;

	temp_nptr = nptr;

    if(temp_nptr == NULL)
    {
        return 0;
    }

    if(strlen(temp_nptr) == 0)
    {
        return 0;
    }
	
	while (*temp_nptr == ' ')  
	{
		temp_nptr++;
	}

	if((base == 0 || base == 16)
	&& (*temp_nptr == '0')
	&& (temp_nptr[1] == 'X' || temp_nptr[1] == 'x'))
	{
		temp_nptr += 2;
		base = 16;
	}

	if(base == 0)
	{
		base = (*temp_nptr == '0' ? 8 : 10);
		temp_nptr++;
	}

    switch(base)
    {
		case 2:
			if(!(*temp_nptr >= '0' && *temp_nptr <= '1'))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;
		
		case 8:
			if(!(*temp_nptr >= '0' && *temp_nptr <= '7'))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;
		
		case 10:
			if(!(*temp_nptr >= '0' && *temp_nptr <= '9'))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;

		case 16:
			if(!((*temp_nptr >= '0' && *temp_nptr <= '9') 
			|| (*temp_nptr >= 'a' && *temp_nptr <= 'f')
			|| (*temp_nptr >= 'A' && *temp_nptr <= 'F')))
			{
				err_flag = 1;
			}
			else
			{
				err_flag = 0;
			}
		break;

		default:
			err_flag = 0;
		break;
	}

	if(err_flag == 1)
	{
		*endptr = temp_nptr;
		return 0;
	}
	else
	{
		val = strtoul(temp_nptr, endptr, base);
	}
	return val;
}

