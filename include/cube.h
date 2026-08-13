#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define WIN_W 1280
# define WIN_H 720

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_F 4
# define TEX_C 5

# define KEY_W 0
# define KEY_A 1
# define KEY_S 2
# define KEY_D 3
# define KEY_LEFT 4
# define KEY_RIGHT 5
# define KEY_COUNT 6

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363
# define K_ESC 65307

# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	*file_name;
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_scene
{
	char	*tex_path[4];
	int		floor;
	int		ceiling;
	t_map	map;
	double	start_x;
	double	start_y;
	char	start_dir;
}	t_scene;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	perp_dist;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_id;
}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	frame;
	t_img	tex[4];
	t_scene	*scene;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	frame_time;
	int		keys[KEY_COUNT];
}	t_game;

int		parse_scene(char *map_file, t_scene *scene);
int		run_game(t_scene *scene);
void	free_scene(t_scene *scene);
int		error_msg(char *msg);

/*
	parsing_utils.c
*/
int		is_line_empty(char *line);
int		validate_file(char *map_file);
int		is_tex_id_used(int tex_id, t_scene *scene);
int		handle_unknown_line(char *line, char **first_map_line, int counter);
int		identify_element(char *line);
int		dispatch_element(char *line, int tex_id, t_scene *scene);

#endif
