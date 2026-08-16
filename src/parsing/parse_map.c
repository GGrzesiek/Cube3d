#include "cube.h"

int add_map_line(t_map_line **head, char *raw_line)
{
	char    *clean;
	t_map_line *node;

	clean = ft_strtrim(raw_line, "\n\r");
	if (!clean)
		return (error_msg("malloc error in add_map_line :("));
	node = new_map_line(clean);
	if (!node)
	{
		free(clean);
		return (error_msg("Malloc error :("));
	}
	add_map_line_back(head, node);
	return (0);
}

int process_map_line(char *line, t_map_line **lines, int *map_ended)
{
	if (is_line_empty(line))
	{
		*map_ended = 1;
		return (0);
	}
	if (*map_ended)
        return (error_msg("Empty line inside map"));
	return (add_map_line(lines, line));
}

int collect_map_lines(int fd, char *first_line, t_map_line **lines)
{
	char	*line;
	int		map_ended;

	if (add_map_line(lines, first_line))
		return (1);
	map_ended = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_map_line(line, lines, &map_ended))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}


int parse_map(int fd, t_scene *scene, char *first_map_line)
{
	t_map_line	*lines;

	lines = NULL;
	if (collect_map_lines(fd, first_map_line, &lines))
	{
		free(first_map_line);
		free_map_lines(&lines);
		return (error_msg("map parsing error"));
	}
	free(first_map_line);
	if (create_map(scene, &lines))
		return (1);
	free_map_lines(&lines);
	if (validate_map(scene))
		return (1);
	return (0);
}
