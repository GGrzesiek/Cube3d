/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:49:43 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 13:49:43 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// int main(void)
// {
//     char *test[] = {
//         strdup("aaaaaaa"),
//         strdup("abcdefg"),
//         strdup("ABCDEFG"),
//         strdup("000"),
//         strdup("ala ma kota")
//     };
//     int i = 0;
//     while (i < sizeof(test) / sizeof(test[0]))
//     {
//         printf("str: %s\n", test[i]);
//         ft_striteri(test[i], to_uppercase);
//         printf("res: %s\n", test[i]);
//         printf("------------------------------------\n");
//         free(test[i]);
//         i++;
//     }
// }