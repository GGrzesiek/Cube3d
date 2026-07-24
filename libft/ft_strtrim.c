/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:45:34 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:45:34 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*res;
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;

	start = 0;
	i = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	res = (char *)malloc((end - start + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (start < end)
	{
		res[i] = s1[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

// int main(void)
// {
//     char *ptr;
// 	char *s1 = "ABChello!AB";
// 	char *set = "ABCD";
// 	printf("s1:\t%s\n", s1);
// 	printf("set:\t%s\n", set);
//     ptr = ft_strtrim(s1, set);
//     int i = 0;
// 	printf("result: %s\n", ptr);
//     while (ptr[i])
//     {
//         printf("%c\t%d\n", ptr[i], ptr[i]);
//         i++;
//     }
//     printf("%c\t%d\n", ptr[i], ptr[i]);
// }