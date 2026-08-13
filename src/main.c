#include "cube.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (error_msg("usage: ./cub3D <scenefile.cub>"));
	if (parse_scene(argv[1], &scene))
		return (1);
	return (0);
}
