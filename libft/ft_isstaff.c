/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstaff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:23:23 by rmrok             #+#    #+#             */
/*   Updated: 2025/01/03 12:44:03 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int	ft_isprint(int c)
{
	return (c >= '!' && c <= '~');
}

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// int main()
// {
// 	char c;

// 	c = '1';
// 	printf("char\tfunc()\tft_funct()\n");
// 	printf("%c\t%d\t%d\n", c, isalpha(c), ft_isalpha(c));
// 	c = 'a';
// 	printf("%c\t%d\t%d\n", c, isalpha(c), ft_isalpha(c));
// 	c = '\t';
// 	printf("%c\t%d\t%d\n", c, isprint(c), ft_isprint(c));
// 	c = ' ';
// 	printf("%c\t%d\t%d\n", c, isprint(c), ft_isprint(c));
// 	c = 'd';
// 	printf("%c\t%d\t%d\n", c, isprint(c), ft_isprint(c));
// 	return (0);
// }