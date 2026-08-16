#include "cube.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	if_player(char cell, t_scene *scene, int y, int x)
{
	if (is_player(cell))
	{
		scene->start_dir = cell;
		scene->start_x = (double)x + 0.5 + 1;
		scene->start_y = (double)y + 0.5 - 1;
	}
}


void	get_size(t_map_line **head, t_scene *scene)
{
	t_map_line  *curr;
	int         height;
	int			width;
	int			width_max;

	curr = *head;
	height = 1;
	width_max = 0;
	while (curr->next)
	{
		height++;
		width = 0;
		while (curr->content[width])
		{
			if_player(curr->content[width], scene, height, width);
			width++;
		}
		if (width > width_max)
			width_max = width;
		curr=curr->next;
	}
	scene->map.height = height;
	scene->map.width = width_max;
}


void	read_map(t_map_line **head, t_scene *scene)
{
	t_map_line  *curr;
	int         i;
	int			width;


	curr = *head;
	i = 0;
	while (curr->next)
	{
		scene->map.grid[i] = ft_strdup(curr->content);
		curr=curr->next;
		i++;
	}
	scene->map.grid[i] = NULL;
}

int create_map(t_scene *scene, t_map_line **head)
{
	get_size(head, scene);
	scene->map.grid = malloc((scene->map.height + 1) * sizeof(char *));
	if (!scene->map.grid)
		return (error_msg("malloc error in create_map :("));
	read_map(head, scene);
	return (0);
}