/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:06:10 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 13:09:00 by rmrok            ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	num;

	len = count_len(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
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
		res[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (res);
}

// int main()
// {
//     int tests[] = {
//         123456789,
//         -123456789,
//         INT_MIN,
//         INT_MAX,
//         0,
//         23,
// 		-2,
// 		2
//     };
//     char *str;
//     size_t i = 0;
//     while (i < sizeof(tests) / sizeof(int))
//     {
//         printf("number:\t\t%d\n", tests[i]);
//         str = ft_itoa(tests[i]);
//         printf("as ascii:\t%s\n", str);
//         printf("------------------------------\n");
// 		free(str);
//         i++;
//     }
// }
