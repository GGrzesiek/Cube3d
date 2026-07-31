#include "cube.h"

int validate_file(char *file_str)
{
	int file_ptr;

	file_ptr = open(file_str, O_RDONLY);
	if (file_ptr < 0)
	{
		printf("Error\nCould not open file: %s\n", file_str);
		return (1);
	}
	close(file_ptr);
	return (0);	
}

int identify_texture(char *line)
{
    if (line[0] == 'N' && line[1] == 'O')
        return (TEX_NO);
    if (line[0] == 'S' && line[1] == 'O')
        return (TEX_SO);
    if (line[0] == 'W' && line[1] == 'E')
        return (TEX_WE);
    if (line[0] == 'E' && line[1] == 'A')
        return (TEX_EA);
	if (line[0] == 'F' && line[1] == ' ')
		return (TEX_F);
	if (line[0] == 'C' && line[1] == ' ')
		return (TEX_C);
    return (-1);
}

/*
	to do: check for duplicates, check for valid paths, check for valid colors
*/
int parse_scene_info(int file_ptr, t_scene *scene)
{
	char	*line;
	char	*trimmed_line;
	int		tex_index;
	int		counter;

	counter = 0;
	line = get_next_line(file_ptr);
	while (line)
	{
		trimmed_line = ft_strtrim(line, " \t\n");
		if (trimmed_line[0] == '\0')
			;
		else if ((tex_index = identify_texture(trimmed_line)) != -1)
		{
			scene->tex_path[tex_index] = ft_strdup(trimmed_line + 2);
			counter++;
		}
		if (counter == 6)
		{
			free(trimmed_line);
			free(line);
			break ;
		}
		free(trimmed_line);
		free(line);
		line = get_next_line(file_ptr);
	}
	return (0);
}

// int parse_map(int file_ptr, t_scene *scene)
// {

// }

int	read_map_file(char *map_file, t_scene *scene)
{
	int	file_ptr;
	
	printf("Reading map file: %s\n", map_file);
	if (validate_file(map_file))
		return (1);
	file_ptr = open(map_file, O_RDONLY);

	if (parse_scene_info(file_ptr, scene))
		return (1);
	// if (parse_map(file_ptr, scene))
	// 	return (1);

	char *line = get_next_line(file_ptr);
	printf("First line of map: \n%s\n", line);
	close(file_ptr);
	return (0);
}

int parse_scene(char *map_file, t_scene *scene)
{

	if (read_map_file(map_file, scene))
		return (1);
	printf("Texture paths:\nNO: %s\nSO: %s\nWE: %s\nEA: %s\nF: %s\nC: %s\n", 
		scene->tex_path[TEX_NO], scene->tex_path[TEX_SO], scene->tex_path[TEX_WE],
		scene->tex_path[TEX_EA], scene->tex_path[TEX_F], scene->tex_path[TEX_C]);

	return (0);
}