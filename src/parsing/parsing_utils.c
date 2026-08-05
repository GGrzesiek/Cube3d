#include "cube.h"

int is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int validate_file(char *map_file)
{
	size_t	len;

	if (!map_file)
		return (error_msg("No map file provided"));
	len = ft_strlen(map_file);
	if (len < 5)
		return (error_msg("Filename too short (need name.cub)"));
	if (ft_strncmp(map_file + len - 4, ".cub", 4) != 0)
		return (error_msg("File must have .cub extension"));
	return (0);	
}

int	is_tex_id_used(int tex_ID,  t_scene *scene)
{
	if (scene->tex_path[tex_ID])
		return (1);
	return (0);
}

int handle_unknown_line(char *line, char **first_map_line, int counter)
{
    if (counter < 6)
    {
        free(line);
        return (error_msg("Unexpected line before all elements set"));
    }
    *first_map_line = line;
    return (0);
}

int identify_element(char *line)
{
    if (line[0] == 'N' && line[1] == 'O')
        return (TEX_NO);
    if (line[0] == 'S' && line[1] == 'O')
        return (TEX_SO);
    if (line[0] == 'W' && line[1] == 'E')
        return (TEX_WE);
    if (line[0] == 'E' && line[1] == 'A')
        return (TEX_EA);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (TEX_F);
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (TEX_C);
    return (-1);
}
