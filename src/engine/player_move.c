#include "cube.h"

static int	is_wall(t_game *g, double x, double y)
{
	int		mx;
	int		my;
	char	c;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= g->scene->map.width)
		return (1);
	if (my < 0 || my >= g->scene->map.height)
		return (1);
	c = g->scene->map.grid[my][mx];
	return (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W');
}

static void	try_move(t_game *g, double dx, double dy)
{
	if (!is_wall(g, g->pos_x + dx, g->pos_y))
		g->pos_x += dx;
	if (!is_wall(g, g->pos_x, g->pos_y + dy))
		g->pos_y += dy;
}

void	move_player(t_game *g)
{
	double	step;
	double	side_x;
	double	side_y;

	step = MOVE_SPEED * g->frame_time;
	side_x = g->plane_x / FOV_PLANE;
	side_y = g->plane_y / FOV_PLANE;
	if (g->keys[KEY_W])
		try_move(g, g->dir_x * step, g->dir_y * step);
	if (g->keys[KEY_S])
		try_move(g, -g->dir_x * step, -g->dir_y * step);
	if (g->keys[KEY_A])
		try_move(g, -side_x * step, -side_y * step);
	if (g->keys[KEY_D])
		try_move(g, side_x * step, side_y * step);
}
