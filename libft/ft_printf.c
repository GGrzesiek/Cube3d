/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:03:26 by rmrok             #+#    #+#             */
/*   Updated: 2025/03/10 13:25:58 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_format(const char f, va_list args)
{
	if (f == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (f == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (f == 'p')
		return (put_pointer(va_arg(args, uintptr_t)));
	else if (f == 'd' || f == 'i')
		return (put_int(va_arg(args, int)));
	else if (f == 'u')
		return (put_u_int(va_arg(args, unsigned int)));
	else if (f == 'x' || f == 'X')
		return (put_hex(va_arg(args, unsigned int), f));
	else if (f == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		length;
	size_t	i;

	if (!format)
		return (-1);
	length = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			length += read_format(format[i + 1], args);
			i++;
		}
		else
			length += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (length);
}
