#include "cube.h"

static char	*pad_row(char *src, int width)
{
	char	*row;
	int		i;

	row = malloc(width + 1);
	if (!row)
		return (NULL);
	i = 0;
	while (src[i] && i < width)
	{
		row[i] = src[i];
		i++;
	}
	while (i < width)
	{
		row[i] = ' ';
		i++;
	}
	row[width] = '\0';
	return (row);
}

static void	scan_player(t_scene *scene, char *row, int y)
{
	int	x;

	x = 0;
	while (row[x])
	{
		if (is_player(row[x]))
		{
			scene->start_dir = row[x];
			scene->start_x = (double)x + 0.5;
			scene->start_y = (double)y + 0.5;
		}
		x++;
	}
}

static int	fill_rows(t_scene *scene, t_map_line *curr)
{
	int	i;

	i = 0;
	while (curr)
	{
		scene->map.grid[i] = pad_row(curr->content, scene->map.width);
		if (!scene->map.grid[i])
			return (error_msg("malloc error in build_grid :("));
		scan_player(scene, scene->map.grid[i], i);
		check_for_dir(scene, curr->content);
		curr = curr->next;
		i++;
	}
	return (0);
}

/* ft_calloc, not malloc: a pad_row failure at row k leaves grid[k..height]
   NULL, so free_tab stops at the first NULL and frees exactly what exists. */
int	build_grid(t_scene *scene, t_map_line **head)
{
	scene->map.grid = ft_calloc(scene->map.height + 1, sizeof(char *));
	if (!scene->map.grid)
		return (error_msg("malloc error in build_grid :("));
	return (fill_rows(scene, *head));
}
