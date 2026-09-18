/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:18:34 by rmrok             #+#    #+#             */
/*   Updated: 2026/09/18 16:18:35 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

static void	get_size(t_map_line **head, t_scene *scene)
{
	t_map_line	*curr;
	int			height;
	int			width;

	curr = *head;
	height = 0;
	scene->map.width = 0;
	while (curr)
	{
		height++;
		width = (int)ft_strlen(curr->content);
		if (width > scene->map.width)
			scene->map.width = width;
		curr = curr->next;
	}
	scene->map.height = height;
}

int	create_map(t_scene *scene, t_map_line **head)
{
	get_size(head, scene);
	return (build_grid(scene, head));
}
