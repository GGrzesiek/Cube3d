/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:45:03 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:45:03 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	unsigned int	i;
	char			*ptr;

	i = 0;
	len = ft_strlen(s);
	ptr = (char *)malloc(len * sizeof(char) + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main()
// {
//     char s[] = "123456789";

//     char *ptr = ft_strdup(s);
//     printf("s:\t%s\t%p\n", s, s);
//     printf("ptr:\t%s\t%p\n", ptr, ptr);
// }