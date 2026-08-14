#include "cube.h"

void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
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
