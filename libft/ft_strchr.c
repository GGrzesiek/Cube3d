/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:05:34 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/05 21:05:34 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ans;

	ans = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			ans = (char *)s;
			return (ans);
		}
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	int c;
// 	char *test = "tripouille";
// 	c = 't';
// 	printf("%s\n", ft_strchr(test, c));
// 	printf("%s\n", strchr(test, c));
// 	printf("\n");
// 	c = 'l';
// 	printf("%s\n", ft_strchr(test, c));
// 	printf("%s\n", strchr(test, c));
// 	printf("\n");
// 	c = 'z';
// 	printf("%s\n", ft_strchr(test, c));
// 	printf("%s\n", strchr(test, c));
// 	printf("\n");
// 	c = 0;
// 	printf("%s\n", ft_strchr(test, c));
// 	printf("%s\n", strchr(test, c));
// 	printf("\n");
// 	c = 't' + 256;
// 	printf("%s\n", ft_strchr(test, c));
// 	printf("%s\n", strchr(test, c));
// 	printf("\n");

// 	if (strchr(test, 'x') == NULL)
// 		printf("NULL\n");
// 	if (ft_strchr(test, 'x') == NULL)
// 		printf("NULL\n");
// }