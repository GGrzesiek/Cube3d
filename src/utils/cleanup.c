#include "cube.h"

static void	destroy_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->tex[i].ptr)
			mlx_destroy_image(g->mlx, g->tex[i].ptr);
		g->tex[i].ptr = NULL;
		i++;
	}
}

void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
	destroy_textures(g);
	if (g->frame.ptr)
		mlx_destroy_image(g->mlx, g->frame.ptr);
	g->frame.ptr = NULL;
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	g->win = NULL;
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	g->mlx = NULL;
	free_scene(g->scene);
}
