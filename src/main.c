#include "cube.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (error_msg("usage: ./cub3D <scenefile.cub>"));
	ft_bzero(&scene, sizeof(t_scene));
	if (parse_scene(argv[1], &scene))
		return (1);
	if (stub_fill_scene(&scene))
		return (free_scene(&scene), 1);
	return (run_game(&scene));
}
