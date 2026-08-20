#include "cube.h"

/*
    validation to do:
    - check if map contains only: 0, 1, ' ', {N, S, W, E} - done
    - check if there is only one of {N, S, W, E} - done
    - The map must be closed/surrounded by walls,
        if not the program must return an error
*/

/*
    checks if map contains only: 0, 1, ' ', {N, S, W, E}
*/
int validate_line(char *map_line)
{
    int     i;
    char    c;

    i = 0;
    while (map_line[i])
    {
        c = map_line[i];
        if (!(is_player(c) ||
            c == '0' || c == '1' || c == ' '))
            return (error_msg("Invalid map character"));
        i++;
    }
    return (0);
}
/*
    counts N, S, W, E
*/
void    check_for_dir(t_scene *scene, char *line)
{
    int     i;

    i = 0;
    while (line[i])
    {
        if (is_player(line[i]))
            scene->dir_count++;
        i++;
    }
}

int near_space(int i, int j, char **g)
{
    if (g[i + 1][j] == ' ' || g[i + 1][j] == '\0')
        return (1);
    if (g[i - 1][j] == ' ' || g[i - 1][j] == '\0')
        return (1);
    if (g[i][j - 1] == ' ' || g[i][j - 1] == '\0')
        return (1);
    if (g[i][j + 1] == ' ' || g[i][j + 1] == '\0')
        return (1);
    if (g[i + 1][j + 1] == ' ' || g[i + 1][j + 1] == '\0')
        return (1);
    if (g[i - 1][j + 1] == ' ' || g[i - 1][j + 1] == '\0')
        return (1);
    if (g[i + 1][j - 1] == ' ' || g[i + 1][j - 1] == '\0')
        return (1);
    if (g[i - 1][j - 1] == ' ' || g[i - 1][j - 1] == '\0')
        return (1);
    return (0);
}

int is_enclosed(t_scene *scene)
{
    char    **map_grid;
    int     i;
    int     j;

    i = 0;
    map_grid = scene->map.grid;
    while (i < scene->map.height)
    {
        j = 0;
        while (j < scene->map.width)
        {
            if (map_grid[i][j] == '0' || is_player(map_grid[i][j]))
            {
                if (i == 0 || i == scene->map.height - 1)
                    return (1);
                if (j == 0 || j == scene->map.width - 1)
                    return (1);
                if (near_space(i, j, map_grid))
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int validate_map(t_scene *scene)
{
    if (scene->dir_count != 1)
        return (error_msg("Invalid amount of direction characters"));
    if (scene->map.height < 3)
        return (error_msg("Map is too small"));
    if (scene->map.width < 3)
        return (error_msg("Map is too small"));
    if (is_enclosed(scene))
        return (error_msg("Map in not enclosed"));
    return (0);
}