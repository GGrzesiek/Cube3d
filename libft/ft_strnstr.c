/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:53:44 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/05 20:53:44 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (!small[0])
		return ((char *)big);
	if (!len)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == small[0])
		{
			j = 0;
			while (big[i + j] == small[j] && i + j < len)
			{
				if (!small[j + 1])
					return ((char *)big + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// void	test_ft_strnstr(void)
// {
// 	char big[30] = "aaabcabcd";
// 	char small[] = "aabc";
// 	size_t len = 0;
// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", small);
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", (char *)NULL);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(big, small, len));

// 	len = -1;
// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", small);
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", big + 1);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(big, small, len));

// 	len = -1;
// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", "a");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", big);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(big, "a", len));

// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", "c");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", big + 4);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(big, "c", len));

// 	char *empty = (char *)"";
// 	printf("big:\t\t%s\n", empty);
// 	printf("small:\t\t%s\n", "");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", empty);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(empty, "", len));

// 	len = 0;
// 	printf("big:\t\t%s\n", empty);
// 	printf("small:\t\t%s\n", "");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", empty);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(empty, "", len));

// 	len = -1;
// 	printf("big:\t\t%s\n", empty);
// 	printf("small:\t\t%s\n", "coucou");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", (char *)NULL);
// 	printf("got:\t\t%s\n\n\n", ft_strnstr(empty, "coucou", len));

// 	len = 5;
// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", "aaabc");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", big);
// 	printf("got:\t\t\t%s\n\n\n", ft_strnstr(big, "aaabc", len));

// 	len = 5;
// 	printf("big:\t\t%s\n", empty);
// 	printf("small:\t\t%s\n", "12345");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", (char *)NULL);
// 	printf("got:\t\t\t%s\n\n\n", ft_strnstr(big, "12345", len));

// 	len = 9;
// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", "abcd");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\t\t%s\n", big + 5);
// 	printf("got:\t\t\t%s\n\n\n", ft_strnstr(big, "abcd", len));

// 	len = 8;
// 	printf("big:\t\t%s\n", big);
// 	printf("small:\t\t%s\n", "cd");
// 	printf("len:\t\t%lu\n", len);
// 	printf("expected:\tNULL\n");
// 	printf("got:\t\t\t%s\n\n\n", ft_strnstr(big, "cd", len));
// }

// int	main(void)
// {
// 	// printf("atoi -1: %d\n", atoi("-1"));
// 	// printf("atoi as size_t: %lu\n", (size_t)atoi("-1"));
// 	test_ft_strnstr();
// }