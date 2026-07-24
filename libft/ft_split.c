/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:44:57 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:44:57 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_words(char const *s, char c)
{
	unsigned int	words;
	unsigned int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (s[i + 1] == c || !s[i + 1])
				words++;
			i++;
		}
	}
	return (words);
}

static unsigned int	get_world_len(char const *s, char c, unsigned int *j)
{
	unsigned int	len;

	len = 0;
	while (s[*j] && s[*j] != c)
	{
		len++;
		(*j)++;
	}
	return (len);
}

static void	write_words(char **res, unsigned int words, char c, char const *s)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;
	unsigned int	index;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		len = get_world_len(s, c, &j);
		res[i] = (char *)malloc((len + 1) * sizeof(char));
		j -= len;
		index = 0;
		while (s[j] && s[j] != c)
		{
			res[i][index] = s[j];
			index++;
			j++;
		}
		res[i][index] = '\0';
		i++;
	}
	res[words] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	unsigned int	words;

	words = count_words(s, c);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	write_words(res, words, c, s);
	return (res);
}

// int main()
// {
//     char s[] = "  tripouille  42  ";
// 	char c = ' ';
//     char **ptr;

//     ptr = ft_split(s, c);
//     int i = 0;
//     int j;
//     while (ptr[i])
//     {
//         j = 0;
//         while (ptr[i][j])
//         {
//             printf("%c", ptr[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
// }