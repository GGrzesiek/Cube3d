/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:14:04 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 13:14:04 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned int	i;
	unsigned char	c2;

	i = 0;
	c2 = c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (*ptr == c2)
			return ((void *)ptr);
		ptr++;
		i++;
	}
	return (NULL);
}

// int main() {
//     char buffer[] = "Hello, memchr test!";
//     int test_char = 'm';
//     size_t len = 20;

//     void *original_result = memchr(buffer, test_char, len);
//     void *custom_result = ft_memchr(buffer, test_char, len);

//     printf("Buffer: \"%s\"\n", buffer);
//     printf("Character to search: '%c'\n", test_char);
//     printf("Length to search: %zu\n", len);

//     if (original_result) {
//         printf("Original memchr found: '%c' at position: %ld\n",
//                *(char *)original_result, (char *)original_result - buffer);
//     } else {
//         printf("Original memchr did not find the character.\n");
//     }

//     if (custom_result) {
//         printf("Custom ft_memchr found: '%c' at position: %ld\n",
//                *(char *)custom_result, (char *)custom_result - buffer);
//     } else {
//         printf("Custom ft_memchr did not find the character.\n");
//     }

//     return (0);
// }
