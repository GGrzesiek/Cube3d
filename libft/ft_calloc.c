/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/03 12:59:20 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:59:20 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	size_t	i;
	char	*ptr;

	i = 0;
	if (nmemb > 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < total_size)
		ptr[i++] = 0;
	return ((void *)ptr);
}

// int main(void)
// {
//     printf("lets test it!\n");

//     int *ptr = (int *)ft_calloc(5, sizeof(int));

//     int i = 0;
//     while (i < 5)
//     {
//         printf("ptr[%u] = %d\n", i, ptr[i]);
//         i++;
//     }
//     free(ptr);
// }
