/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:45:10 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:45:10 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	unsigned int	i;
	char			*ptr;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(s1_len + s2_len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		ptr[s1_len + i] = s2[i];
		i++;
	}
	ptr[s1_len + i] = '\0';
	return (ptr);
}

// int main(void)
// {
//     char s1[] = "hello,";
//     char s2[] = " world!";
//     char *ptr;

//     ptr = ft_strjoin(s1, s2);
//     printf("%s\n", ptr);
// }