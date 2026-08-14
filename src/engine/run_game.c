#include "cube.h"

static int	setup_image(t_game *g)
{
	g->frame.ptr = mlx_new_image(g->mlx, WIN_W, WIN_H);
	if (!g->frame.ptr)
		return (1);
	g->frame.addr = mlx_get_data_addr(g->frame.ptr, &g->frame.bpp,
			&g->frame.line_len, &g->frame.endian);
	if (!g->frame.addr)
		return (1);
	g->frame.width = WIN_W;
	g->frame.height = WIN_H;
	return (0);
}

static int	setup_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (1);
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "cub3D");
	if (!g->win)
		return (1);
	return (setup_image(g));
}

int	run_game(t_scene *scene)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.scene = scene;
	if (setup_mlx(&game))
		return (error_msg("MiniLibX setup failed"));
	register_hooks(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
