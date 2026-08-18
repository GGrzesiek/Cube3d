#include "cube.h"

void	update_frame_time(t_game *g)
{
	struct timeval	now;
	long			us;

	gettimeofday(&now, NULL);
	us = now.tv_sec * 1000000L + now.tv_usec;
	if (g->last_us == 0)
		g->last_us = us;
	g->frame_time = (double)(us - g->last_us) / 1000000.0;
	g->last_us = us;
	if (g->frame_time > 0.1)
		g->frame_time = 0.1;
}

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
	init_player(&game);
	if (setup_mlx(&game))
		return (cleanup_game(&game), error_msg("MiniLibX setup failed"));
	if (load_textures(&game))
		return (cleanup_game(&game), 1);
	register_hooks(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
