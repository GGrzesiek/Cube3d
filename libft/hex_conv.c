/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:10:00 by rmrok             #+#    #+#             */
/*   Updated: 2025/03/10 13:27:21 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_it(char *str)
{
	char	c;
	int		len;
	int		i;

	len = ft_strlen(str) - 1;
	i = 0;
	while (i < len)
	{
		c = str[i];
		str[i] = str[len];
		str[len] = c;
		i++;
		len--;
	}
}

int	hex_conv(unsigned long num, char f)
{
	int		i;
	char	*res;
	char	*base;

	base = "0123456789abcdef";
	res = (char *)malloc(17 * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (num)
	{
		res[i] = base[num % 16];
		if (f == 'X')
			res[i] = ft_toupper(res[i]);
		num /= 16;
		i++;
	}
	res[i] = '\0';
	swap_it(res);
	i = ft_strlen(res);
	ft_putstr(res);
	free(res);
	return (i);
}

int	put_hex(unsigned int num, char f)
{
	int	len;

	if (num == 0)
		return (ft_putchar('0'));
	len = hex_conv((unsigned long)num, f);
	return (len);
}
