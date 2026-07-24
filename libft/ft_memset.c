/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:49:35 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:44:36 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*dest;

	dest = str;
	i = 0;
	while (i < n)
		dest[i++] = (unsigned char)c;
	return ((void *)dest);
}

// int	main(void)
// {
// 	char str[50] = "GeeksForGeeks is for programming geeks.";
// 	printf("\nBefore memset(): %s\n", str);

// 	memset(str + 13, '.', 8 * sizeof(char));

// 	printf("After memset():  %s\n", str);

// 	char str2[50] = "GeeksForGeeks is for programming geeks.";
// 	printf("\nBefore ft_memset(): %s\n", str2);

// 	ft_memset(str2 + 13, '.', 8 * sizeof(char));
// 	printf("After ft_memset():  %s", str2);

// 	printf("\n%c\n", 32);
// 	return (0);
// }