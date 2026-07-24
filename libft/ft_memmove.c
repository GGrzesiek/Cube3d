/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:44:32 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 13:28:43 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s)
		return (dest);
	else if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}

// int main(void)
// {
//     char str[] = "123456789";
//     memmove(str + 3, str, 4);
//     printf("%s\n", str);

//     char str2[] = "123456789";
//     memmove(str2 + 3, str2, 4);
//     printf("%s\n\n", str2);

//     char str3[] = "123456789";
//     memmove(str3, str3 + 3, 4);
//     printf("%s\n", str3);

//     char str4[] = "123456789";
//     memmove(str4, str4 + 3, 4);
//     printf("%s\n", str4);
// }
