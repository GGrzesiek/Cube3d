#include "cube.h"

#define STUB_W 24
#define STUB_H 15

static const char *const	g_stub_map[STUB_H] = {
	"111111111111111111111111",
	"100000000000000000000001",
	"101111101111101111101101",
	"100000100000100000100101",
	"111110101110101110101101",
	"100000101000101000100001",
	"101111101011101011111101",
	"101000001010001010000001",
	"101011111010111010111101",
	"101010000010100010100001",
	"101010111110101110101111",
	"100010100000100000100001",
	"111110101111111111101101",
	"1E0000000000000000000001",
	"111111111111111111111111"
};

static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static char	**dup_grid(void)
{
	char	**grid;
	int		i;

	grid = ft_calloc(STUB_H + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < STUB_H)
	{
		grid[i] = ft_strdup(g_stub_map[i]);
		if (!grid[i])
			return (free_grid(grid), NULL);
		i++;
	}
	return (grid);
}

int	stub_fill_scene(t_scene *scene)
{
	scene->map.grid = dup_grid();
	if (!scene->map.grid)
		return (error_msg("Malloc error :("));
	scene->map.width = STUB_W;
	scene->map.height = STUB_H;
	scene->floor = 0x6B4A2F;
	scene->ceiling = 0x2E4A6B;
	scene->start_x = 1.5;
	scene->start_y = 13.5;
	scene->start_dir = 'E';
	return (0);
}

void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	i = 0;
	while (i < 4)
	{
		free(scene->tex_path[i]);
		scene->tex_path[i] = NULL;
		i++;
	}
	free_grid(scene->map.grid);
	scene->map.grid = NULL;
	free(scene->map.file_name);
	scene->map.file_name = NULL;
}
