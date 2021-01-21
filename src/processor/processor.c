#include "../include/ft_printf.h"

// left flags: pxX%
// do flags: p
// done flags: suidc
void run_processor(struct s_flags *flag, va_list *ap)
{
	if (DEBUG)
		printf("\nDEBUG MODE: Input data to run_processor\n");
	if (DEBUG_FLAGS)
		print_flags(flag);

	if (flag->width == -1)
		flag->width = va_arg(*ap, int);
	if (flag->precision == -1)
		flag->precision = va_arg(*ap, int);

	if (flag->conversion == CHAR)
	{
		if (DEBUG)
			printf("This is CHAR\n");
		draw_char(flag, ap);
	}

	if (flag->conversion == STRING)
	{
		if (DEBUG)
			printf("This is STRING\n");
		draw_string(flag, ap);
	}

	if (flag->conversion == U_INTEGER)
	{
		if (DEBUG)
			printf("This is U_INTEGER\n");
		draw_u_integer(flag, ap);
	}

	if (flag->conversion == INTEGER)
	{
		if (DEBUG)
			printf("This is INTEGER\n");
		draw_integer(flag, ap);
	}

	if (flag->conversion == POINTER)
	{
		if (DEBUG)
			printf("This is POINTER\n");
		draw_pointer(flag, ap);
	}

}

char	*fill_line(char *string, int offset, struct s_flags flag)
{
	char	*str;
	char	*str1;

	str = malloc(sizeof(char*) * offset + 1);
	if (str == NULL)
		return (NULL);

	str[offset] = '\0';
	ft_memset(str, flag.zero, offset);
	if (flag.minus)
		str1 = ft_strjoin(string, str);
	else
		str1 = ft_strjoin(str, string);
	free(str);
	free(string);
	return (str1);
}

char	*string_builder(char *string, struct s_flags *flag)
{
	int		offset;

	if (flag->precision)
		if (((int)ft_strlen(string) > flag->precision))
			string[flag->precision] = '\0';
	if (flag->width)
		if ((offset = flag->width - (int)ft_strlen(string)) > 0)
			string = fill_line(string, offset, *flag);
	return (string);
}