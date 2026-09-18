#include "cube.h"

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

/* Idempotent and safe on a partially filled scene: every pointer is freed
   then nulled, so a second call is a no-op. */
void	free_scene(t_scene *scene)
{
	int	i;

	if (!scene)
		return ;
	i = 0;
	while (i < 4)
	{
		free(scene->tex_path[i]);
		scene->tex_path[i] = NULL;
		i++;
	}
	free_tab(&scene->map.grid);
	free(scene->map.file_name);
	scene->map.file_name = NULL;
}
