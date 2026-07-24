/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:43:51 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:43:52 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}

// int main(void) {
//     char str[] = "I hope that function works correctly";
//     char str2[] = "I hope that function works correctly";

//     bzero(str, 12);

//     printf("Result after bzero (byte by byte):\n");
//     for (int i = 0; i < sizeof(str); i++) {
//         if (str[i] == '\0') {
//             printf("\\0 ");
//         } else {
//             printf("%c ", str[i]);
//         }
//     }
//     printf("\n\n");

//     ft_bzero(str2, 12);

//     printf("Result after ft_bzero (byte by byte):\n");
//     for (int i = 0; i < sizeof(str2); i++) {
//         if (str2[i] == '\0') {
//             printf("\\0 ");
//         } else {
//             printf("%c ", str[i]);
//         }
//     }
//     printf("\n\n");
//     return (0);
// }