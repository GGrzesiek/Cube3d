#include "cube.h"

/* facing east = looking at a west face */
void	pick_face(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->dir_x > 0)
			r->tex_id = TEX_WE;
		else
			r->tex_id = TEX_EA;
	}
	else
	{
		if (r->dir_y > 0)
			r->tex_id = TEX_NO;
		else
			r->tex_id = TEX_SO;
	}
}

void	set_wall_x(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->wall_x = g->pos_y + r->perp_dist * r->dir_y;
	else
		r->wall_x = g->pos_x + r->perp_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
}

/* flip or opposite faces come out mirrored */
int	tex_column(t_img *tex, t_ray *r)
{
	int	tex_x;

	tex_x = (int)(r->wall_x * tex->width);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

int	tex_pixel(t_img *tex, int x, int y)
{
	char	*src;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	src = tex->addr + y * tex->line_len + x * (tex->bpp / 8);
	return ((int)*(unsigned int *)src);
}
