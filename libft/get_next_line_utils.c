/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajurczyk <ajurczyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:42:57 by rmrok             #+#    #+#             */
/*   Updated: 2026/03/07 13:09:44 by ajurczyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	char	*res;

// 	res = NULL;
// 	if (!s)
// 		return (res);
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 		{
// 			res = (char *)s;
// 			return (res);
// 		}
// 		s++;
// 	}
// 	if (c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*res;
// 	size_t	len;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	len = ft_countlen(s);
// 	res = (char *)malloc((len + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		res[i] = s[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	long	len1;
// 	long	len2;
// 	long	i;
// 	char	*res;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	len1 = (long)ft_countlen(s1);
// 	len2 = (long)ft_countlen(s2);
// 	res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	i = -1;
// 	while (++i < len1)
// 		res[i] = s1[i];
// 	i = -1;
// 	while (++i < len2)
// 		res[len1 + i] = s2[i];
// 	res[len1 + i] = '\0';
// 	return (res);
// }

// size_t	ft_strlcpy(char *dest, const char *src, size_t size)
// {
// 	size_t	src_len;
// 	size_t	i;

// 	src_len = 0;
// 	while (src[src_len])
// 		src_len++;
// 	if (size == 0)
// 		return (src_len);
// 	i = 0;
// 	while (i < size - 1 && src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (src_len);
// }
