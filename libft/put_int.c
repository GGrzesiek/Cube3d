/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:45:43 by rmrok             #+#    #+#             */
/*   Updated: 2025/03/10 13:26:59 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_itoa_printf(int n)
{
	char			*res;
	int				len;
	unsigned int	num;

	len = count_len(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	if (n == 0)
		res[0] = '0';
	num = (unsigned int)n;
	if (n < 0)
	{
		res[0] = '-';
		num = (unsigned int)n * -1;
	}
	res[len] = '\0';
	while (len - 1 >= 0 && num > 0)
	{
		res[len-- - 1] = (num % 10) + '0';
		num /= 10;
	}
	ft_putstr(res);
	free(res);
	return (count_len(n));
}

int	put_int(int num)
{
	int	len;

	len = ft_itoa_printf(num);
	return (len);
}
