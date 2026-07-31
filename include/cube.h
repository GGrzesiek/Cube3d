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
	char	**grid;      /* space-padded rectangle */
	int		width;
	int		height;
} t_map;


typedef struct s_scene {          /* <-- Person A fills this, Person B consumes it */
	char      	*tex_path[6];       /* indexed by TEX_NO..TEX_EA */
	int			floor;              /* 0xRRGGBB, -1 = unset */
	int			ceiling;
	t_map		map;
	double		start_x;            /* cell centre: (col + 0.5) */
	double		start_y;
	char		start_dir;       /* 'N' 'S' 'E' 'W' */
} t_scene;


int	parse_scene(char *map_file, t_scene *scene);
int error_msg(char *msg);

#endif