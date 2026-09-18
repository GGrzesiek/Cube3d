#include "cube.h"

void	free_grid(char **grid)
{
	int	i;

	if (!grid || !(*grid))
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	grid = NULL;
}

void	free_game(t_scene *scene)
{
	free_grid(scene->map.grid);
}

void	free_tab(char ***tab_ptr)
{
	int	i;

	i = 0;
	if (!tab_ptr || !*tab_ptr)
		return ;
	while ((*tab_ptr)[i])
	{
		free((*tab_ptr)[i]);
		i++;
	}
	free(*tab_ptr);
	*tab_ptr = NULL;
}
