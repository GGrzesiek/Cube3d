/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:45:12 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:45:12 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	dest_i;
	size_t	src_i;

	dest_len = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[dest_len] && dest_len < dstsize)
		dest_len++;
	src_len = ft_strlen(src);
	dest_i = dest_len;
	src_i = 0;
	if (dest_len == dstsize)
		return (dstsize + src_len);
	while (src[src_i] && dest_len + src_i + 1 < dstsize)
	{
		dst[dest_len + src_i] = src[src_i];
		src_i++;
	}
	dst[dest_i + src_i] = '\0';
	return (dest_len + src_len);
}

// int	main(void)
// {
// 	char src[] = "marakuja";
// 	char dest[40] = "kaloryfer";
// 	int x = ft_strlen(dest);
// 	printf("len of dest: %i\n", x);
// 	printf("sizeof(dest): %lu\n", sizeof(dest));
// 	printf("len of src: %i\n", x);
// 	printf("sizeof(src): %lu\n", sizeof(src));

// 	printf("src: %s\ndest: %s\n", src, dest);
// 	size_t result = ft_strlcat(dest, src, 0);
// 	printf("-------------------------\n");
// 	printf("res len: %zu\n", result);
// 	printf("dest after: %s\n", dest);

// 	int i = 0;
// 	while (dest[i])
// 	{
// 		printf("%c\t%d\n", dest[i], dest[i]);
// 		i++;
// 	}
// 	printf("%c\t%d\n", dest[i], dest[i]);
// }