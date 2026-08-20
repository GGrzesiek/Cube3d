#include "cube.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}

void	render_frame(t_game *g)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		cast_ray(g, &ray, x);
		draw_column(g, &ray, x);
		x++;
	}
}

int	game_loop(t_game *g)
{
	update_frame_time(g);
	rotate_player(g);
	move_player(g);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
	return (0);
}
