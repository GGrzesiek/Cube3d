#ifndef CUBE_H
#define CUBE_H

# define WIN_W 1280
# define WIN_H 720
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_F  4
# define TEX_C  5

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
} t_img;

typedef struct s_map {
	char	*file_name;
	char	**grid;
	int		width;
	int		height;
} t_map;


typedef struct s_scene {          /* <-- Person A fills this, Person B consumes it */
	char      	*tex_path[4];      /* indexed by TEX_NO..TEX_EA */
	int			floor;              /* 0xRRGGBB, -1 = unset */
	int			ceiling;
	t_map		map;
	double		start_x;            /* cell centre: (col + 0.5) */
	double		start_y;
	char		start_dir;       /* 'N' 'S' 'E' 'W' */
	int			dir_count;
} t_scene;

typedef struct s_map_line
{
	char				*content;
	struct s_map_line	*next;
}	t_map_line;

int	parse_scene(char *map_file, t_scene *scene);
int error_msg(char *msg);

/*
	parse_color.c
*/
int	parse_color(char *line, int tex_id, t_scene *scene);
/*
	parse_map.c
*/
int parse_map(int fd, t_scene *scene, char *first_map_line);
int create_map(t_scene *scene, t_map_line **head);
int	is_player(char c);
/*
	parsing_utils.c
*/
int is_line_empty(char *line);
int validate_file(char *map_file);
int	is_tex_id_used(int tex_ID,  t_scene *scene);
int handle_unknown_line(char *line, char **first_map_line, int counter);
int identify_element(char *line);
int dispatch_element(char *line, int tex_id, t_scene *scene);
/*
	map_validation.c
*/
int validate_map(t_scene *scene);
int validate_line(char *map_line);
void    check_for_dir(t_scene *scene, char *line);
/*
	list_utils.c
*/
t_map_line *new_map_line(char *content);
void    add_map_line_back(t_map_line **head, t_map_line *node);
void    free_map_lines(t_map_line **head);
/*
	free_utils.c
*/
void    free_game(t_scene *scene);


/*
	printing_debug.c
*/
void	print_map_lines(t_map_line	**head);
void	print_scene_info(t_scene *scene);

#endif