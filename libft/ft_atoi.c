/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:05:59 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/05 21:05:59 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	result;
	int				i;
	int				sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
		result = result * 10 + (nptr[i++] - 48);
	return ((int)result * sign);
}

// void	tester(const char *str)
// {
// 	if (atoi(str) == ft_atoi(str))
// 		printf("OK!\t\t%s: %d\n", str, ft_atoi(str));
// 	else
// 	{
// 		printf("FAIL\nstr: %s\natoi:%d\nft_atoi:%d\n", str, atoi(str),
// 			ft_atoi(str));
// 	}
// 	printf("--------------------------------------------\n");
// }
// int	main(void)
// {
// 	const char *tests[] = {"2",
// 							"11",
// 							"-32",
// 							"2147483647",
// 							"-2147483648",
// 							"1 2",
// 							"1234f532",
// 							"d",
// 							"23f",
// 							" -- 2",
// 							"-+-2"
// 							"-2",
// 							" ++2",
// 							"- 2",
// 							"-- 2",
// 							"+   4",
// 							"    ",
// 							" ",
// 							"\t\t",
// 							NULL};

// 	for (int i = 0; tests[i] != NULL; i++)
// 		tester(tests[i]);
// }
