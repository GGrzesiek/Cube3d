#include "cube.h"

static void	set_bounds(t_ray *r)
{
	r->line_h = (int)(WIN_H / r->perp_dist);
	r->draw_start = -r->line_h / 2 + WIN_H / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + WIN_H / 2;
	if (r->draw_end >= WIN_H)
		r->draw_end = WIN_H - 1;
}

/* halve every channel on y-sides so the two orientations are tellable apart */
static int	shade(int color, int side)
{
	if (side == 1)
		return ((color >> 1) & 0x7F7F7F);
	return (color);
}

void	draw_column(t_game *g, t_ray *r, int x)
{
	int	y;

	set_bounds(r);
	y = 0;
	while (y < r->draw_start)
		put_pixel(&g->frame, x, y++, g->scene->ceiling);
	while (y <= r->draw_end)
		put_pixel(&g->frame, x, y++, shade(WALL_COLOR, r->side));
	while (y < WIN_H)
		put_pixel(&g->frame, x, y++, g->scene->floor);
}
