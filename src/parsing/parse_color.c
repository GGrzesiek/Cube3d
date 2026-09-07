#include "cube.h"

int	is_color_used(int tex_id, t_scene *scene)
{
	if (tex_id == TEX_F && scene->floor != -1)
		return (1);
	if (tex_id == TEX_C && scene->ceiling != -1)
		return (1);
	return (0);
}

void	free_tab(char ***tab_ptr)
{
	int	i;

	i = 0;
	if (!tab_ptr || !*tab_ptr)
		return ;
	while ((*tab_ptr)[i])
	{
		free((*tab_ptr)[i]);
		i++;
	}
	free(*tab_ptr);
	*tab_ptr = NULL;
}

int	validate_color(char *color)
{
	int	i;

	i = 0;
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	if (!color[i])
		return (error_msg("Empty color value"));
	while (ft_isdigit(color[i]))
		i++;
	while (color[i] == ' ' || color[i] == '\t' || color[i] == '\n')
		i++;
	if (color[i])
		return (error_msg("Invalid character in color value"));
	return (0);
}

int	get_color(char *line, int *full_color)
{
	char	**colors;
	int		rgb[3];
	int		i;

	i = 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	colors = ft_split(line + i, ',');
	if (!colors)
		return (1);
	i = 0;
	while (colors[i] && i < 3)
	{
		if (validate_color(colors[i]))
			return (free_tab(&colors), -1);
		rgb[i] = ft_atoi(colors[i]);
		if (!(rgb[i] >= 0 && rgb[i] <= 255))
			return (free_tab(&colors), error_msg("Color Value out of range"));
		i++;
	}
	if (i != 3)
		return (free_tab(&colors), error_msg("Wrong amount of color values"));
	free_tab(&colors);
	*full_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (0);
}

int	parse_color(char *line, int tex_id, t_scene *scene)
{
	int		full_color;

	if (is_color_used(tex_id, scene))
		return (error_msg("Duplicate color identifier"));
	if (get_color(line, &full_color))
		return (1);
	if (tex_id == TEX_C)
		scene->ceiling = full_color;
	else
		scene->floor = full_color;
	return (0);
}
