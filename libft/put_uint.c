/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_uint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:44:09 by rmrok             #+#    #+#             */
/*   Updated: 2025/03/10 13:26:48 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_utoa(unsigned int n)
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
	num = n;
	res[len] = '\0';
	while (len - 1 >= 0 && num > 0)
	{
		res[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	len = ft_strlen(res);
	ft_putstr(res);
	free(res);
	return (len);
}

int	put_u_int(unsigned int num)
{
	int	len;

	len = ft_utoa(num);
	return (len);
}
