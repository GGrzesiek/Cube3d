#include "cube.h"

void	print_map_lines(t_map_line	**head)
{
	printf("--------------\n");
	t_map_line *cur;

	cur = *head;
	while (cur)
	{
		printf("%s\n", cur->content);
		cur = cur->next;
	}
	// printf("last: %s\n", cur->content);
	printf("--------------\n");
}

void	print_scene_info(t_scene *scene)
{
	// ------------------PRINTING VALUES------------------------
	printf("Texture paths:\nNO: %s\nSO: %s\nWE: %s\nEA: %s\nF: 0x%06X\nC: 0x%06X\n", 
		scene->tex_path[TEX_NO], scene->tex_path[TEX_SO], scene->tex_path[TEX_WE],
		scene->tex_path[TEX_EA], scene->floor, scene->ceiling);
	
	printf("map height: %d\n", scene->map.height);
	printf("map width:  %d\n", scene->map.width);

	printf("start x: %f\n", scene->start_x);
	printf("start y: %f\n", scene->start_y);
	printf("start dir: %c\n", scene->start_dir);
	// ----------------------END------------------------

	// ------------------PRINTING MAP------------------------
	int i = 0;
	int j = 0;

	while (scene->map.grid[i])
	{
		printf("%s\n", scene->map.grid[i]);
		i++;
	}
	// ----------------------END------------------------
}