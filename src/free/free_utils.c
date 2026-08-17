#include "cube.h"

void    free_grid(char **grid)
{
    int i;

    if (!grid || !(*grid))
        return ;
    i = 0;
    while (grid[i])
    {
        // printf("grid %i\t: %s\n", i, grid[i]);
        free(grid[i]);
        i++;
    }
    free(grid);
    grid = NULL;
}

void    free_game(t_scene *scene)
{
    free_grid(scene->map.grid);
}