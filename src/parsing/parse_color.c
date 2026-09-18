#include "cube.h"

static int	is_color_used(int tex_id, t_scene *scene)
{
	if (tex_id == TEX_F && scene->floor != -1)
		return (1);
	if (tex_id == TEX_C && scene->ceiling != -1)
		return (1);
	return (0);
}

/* Both checks are needed: ft_split collapses empty tokens, so "1,2,3,4"
   fails on the token count and "0,0,0," only fails on the comma count. */
static int	wrong_count(char *args, char **colors)
{
	int	commas;
	int	tokens;
	int	i;

	commas = 0;
	i = 0;
	while (args[i])
	{
		if (args[i] == ',')
			commas++;
		i++;
	}
	tokens = 0;
	while (colors[tokens])
		tokens++;
	return (commas != 2 || tokens != 3);
}

/* Capping inside the digit loop keeps *value <= 2559, so no count of digits
   can overflow it - which is why ft_atoi is never called on a colour. */
static int	validate_color(char *color, int *value)
{
	int	i;

	i = 0;
	*value = 0;
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	if (!ft_isdigit(color[i]))
		return (error_msg("Color value is not a number"));
	while (ft_isdigit(color[i]))
	{
		*value = *value * 10 + (color[i] - '0');
		if (*value > 255)
			return (error_msg("Color value out of range"));
		i++;
	}
	while (color[i] == ' ' || color[i] == '\t' || color[i] == '\n'
		|| color[i] == '\r')
		i++;
	if (color[i])
		return (error_msg("Invalid character in color value"));
	return (0);
}

static int	get_color(char *line, int *full_color)
{
	char	**colors;
	int		rgb[3];
	int		i;

	i = 1;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	colors = ft_split(line + i, ',');
	if (!colors)
		return (error_msg("Malloc error in get_color :("));
	if (wrong_count(line + i, colors))
		return (free_tab(&colors), error_msg("Wrong amount of color values"));
	i = 0;
	while (i < 3)
	{
		if (validate_color(colors[i], &rgb[i]))
			return (free_tab(&colors), 1);
		i++;
	}
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
