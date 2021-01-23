/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrait <pstrait@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:26:46 by pstrait           #+#    #+#             */
/*   Updated: 2021/01/23 18:20:08 by pstrait          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int processing_nonprintable(char *string, struct s_flags *flag)
{
	char	*str;
	int		offset;
	int		size;

	size = 0;
	if (flag->width)
	{
		if ((offset = flag->width - 1) > 0)
		{
			str = malloc(sizeof(char*) * offset + 1);
			str[offset] = '\0';
			ft_memset(str, flag->zero, offset);
			if (flag->minus)
			{
				ft_putchar(*string);
				ft_putstr(str);
			}
			else
			{
				ft_putstr(str);
				ft_putchar(*string);
			}
			size = ft_strlen(str) + 1;
			free(str);

		}
		else if ((flag->width < 0) && ((flag->width - 1 < 0)))
		{
			flag->minus = 1;
			offset = (flag->width + 1) * -1;
			str = malloc(sizeof(char*) * offset + 1);
			str[offset] = '\0';
			ft_memset(str, flag->zero, offset);
			if (flag->minus)
			{
				ft_putchar(*string);
				ft_putstr(str);
			}
			else
			{
				ft_putstr(str);
				ft_putchar(*string);
			}
			size = ft_strlen(str) + 1;
			free(str);

		}
	}
	else
	{
		ft_putchar(*string);
		size = 1;
	}
	return (size);

}

int	draw_char(struct s_flags *flag, va_list *ap)
{
	char *string;
	int size;

	string = malloc(sizeof(char) * 1 + 1);
	string[0] = (char)va_arg(*ap, int);
	string[1] = '\0';
	size = 0;

	if (ft_strlen(string) == 0)
		size = processing_nonprintable(string, flag);
	else
	{
		string = string_builder(string, flag);
		size = ft_strlen(string);
		ft_putstr(string);
	}
	free(string);
	return (size);
}
