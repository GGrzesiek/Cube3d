#include "cube.h"

int error_msg(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
    {
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
    t_scene scene;

	if (argc != 2)
		return (error_msg("usage: ./cub3D <scenefile.cub>"));
	if (parse_scene(argv[1], &scene))
		return (1);
	return (0);
	// return (run_game(&scene));
}