/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:45:15 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:45:15 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	src_len;
	size_t			i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (n == 0)
		return (src_len);
	i = 0;
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

// int main()
// {
// 	char src[] = "hello world";
// 	char dest[30];

// 	printf("src: %s\n", src);
// 	printf("dest: %s\n", dest);

// 	size_t src_len = ft_strlcpy(dest, src, sizeof(dest));

// 	printf("src: %s\n", src);
// 	printf("dest: %s\n", dest);
// 	printf("src len: %ld\n", src_len);
// }
