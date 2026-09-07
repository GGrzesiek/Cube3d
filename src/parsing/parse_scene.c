#include "cube.h"

int	parse_tex(char *line, int tex_id, t_scene *scene)
{
	int		fd;

	if (is_tex_id_used(tex_id, scene))
		return (error_msg("Duplicate texture identifier"));
	scene->tex_path[tex_id] = ft_strtrim(line + 2, " \t\n");
	if (!scene->tex_path[tex_id])
		return (error_msg("Malloc error :("));
	fd = open(scene->tex_path[tex_id], O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open texture file"));
	close(fd);
	return (0);
}

int	dispatch_element(char *line, int tex_id, t_scene *scene)
{
	if (tex_id == TEX_F || tex_id == TEX_C)
		return (parse_color(line, tex_id, scene));
	return (parse_tex(line, tex_id, scene));
}

int	parse_scene_info(int fd, t_scene *scene, char **first_map_line)
{
	char	*line;
	int		tex_id;
	int		counter;

	counter = 0;
	line = get_next_line(fd);
	while (line)
	{
		tex_id = identify_element(line);
		if (is_line_empty(line))
			;
		else if (tex_id == -1)
			return (handle_unknown_line(line, first_map_line, counter));
		else if (dispatch_element(line, tex_id, scene))
			return (free(line), 1);
		else
			counter++;
		free(line);
		line = get_next_line(fd);
	}
	if (counter < 6)
		return (error_msg("Lack of some scene information"));
	return (error_msg("Missing map"));
}

int	read_map_file(char *map_file, t_scene *scene)
{
	int		fd;
	char	*first_map_line;

	if (validate_file(map_file))
		return (1);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open a file"));
	first_map_line = NULL;
	if (parse_scene_info(fd, scene, &first_map_line))
	{
		free(first_map_line);
		close(fd);
		return (1);
	}
	if (parse_map(fd, scene, first_map_line))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	parse_scene(char *map_file, t_scene *scene)
{
	int	i;

	i = 0;
	scene->floor = -1;
	scene->ceiling = -1;
	scene->dir_count = 0;
	while (i < 4)
		scene->tex_path[i++] = NULL;
	if (read_map_file(map_file, scene))
		return (1);
	if (validate_map(scene))
		return (1);
	return (0);
}
