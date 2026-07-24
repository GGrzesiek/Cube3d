/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:55:49 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/05 20:55:49 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ans;

	ans = NULL;
	while (*s)
	{
		if (*s == (char)c)
			ans = (char *)s;
		s++;
	}
	if (ans != NULL)
		return (ans);
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

// int main(void)
// {
//     char *test = "ala ma kota ala koty ma";
//     printf("%s\n", ft_strrchr(test, 'k'));
//     printf("%s\n", strrchr(test, 'k'));

//     if (strrchr(test, 'x') == NULL)
//         printf("NULL\n");
//     if (ft_strrchr(test, 'x') == NULL)
//         printf("NULL\n");
// }