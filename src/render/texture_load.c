#include "cube.h"

static int	load_one(t_game *g, int i)
{
	g->tex[i].ptr = mlx_xpm_file_to_image(g->mlx, g->scene->tex_path[i],
			&g->tex[i].width, &g->tex[i].height);
	if (!g->tex[i].ptr)
		return (1);
	g->tex[i].addr = mlx_get_data_addr(g->tex[i].ptr, &g->tex[i].bpp,
			&g->tex[i].line_len, &g->tex[i].endian);
	if (!g->tex[i].addr)
		return (1);
	if (g->tex[i].width <= 0 || g->tex[i].height <= 0)
		return (1);
	return (0);
}

int	load_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!g->scene->tex_path[i])
			return (error_msg("Missing a texture path"));
		if (load_one(g, i))
			return (error_msg("Cannot load texture, must be a valid xpm"));
		i++;
	}
	return (0);
}
