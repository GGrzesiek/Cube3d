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

static void	draw_wall(t_game *g, t_ray *r, int x)
{
	t_img	*tex;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		y;

	tex = &g->tex[r->tex_id];
	tex_x = tex_column(tex, r);
	step = (double)tex->height / r->line_h;
	tex_pos = (r->draw_start - WIN_H / 2 + r->line_h / 2) * step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		put_pixel(&g->frame, x, y, tex_pixel(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		y++;
	}
}

void	draw_column(t_game *g, t_ray *r, int x)
{
	int	y;

	set_bounds(r);
	pick_face(r);
	set_wall_x(g, r);
	y = 0;
	while (y < r->draw_start)
		put_pixel(&g->frame, x, y++, g->scene->ceiling);
	draw_wall(g, r, x);
	y = r->draw_end + 1;
	while (y < WIN_H)
		put_pixel(&g->frame, x, y++, g->scene->floor);
}
