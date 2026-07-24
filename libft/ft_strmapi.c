/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:45:21 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:45:21 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	change(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		c = (c - 'a' + i) % 26 + 'a';
	else if (c >= 'A' && c <= 'Z')
		c = (c - 'A' + i) % 26 + 'A';
	return (c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*res;

	len = ft_strlen(s);
	res = (char *)malloc((len + 1) * sizeof(s[0]));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// int main(void)
// {
//     char *test[] = {
//         "aaaaaaa",
//         "abcdefg",
//         "ABCDEFG",
//         "000"
//     };
//     int i = 0;
//     char * str;
//     while (i < sizeof(test) / sizeof(test[0]))
//     {
//         printf("str: %s\n", test[i]);
//         str = ft_strmapi(test[i], change);
//         printf("res: %s\n", str);
//         printf("------------------------------------\n");
//         i++;
//     }
// }