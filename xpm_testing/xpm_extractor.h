# ifndef XPM_EXTRACTOR_H
# define XPM_EXTRACTOR_H

#include "../headers/minirt.h"
#include <stdlib.h>
#include "../mlx_linux/mlx.h"

typedef struct s_texture
{
	char	*filename;

	t_img_info	data;

	int		width;
	int		height;
} t_texture;

t_texture		*texture_init(char *filename, void *mlx);
unsigned int	get_xy_rgb(t_texture *txtr, int x, int y);
t_vec3			*get_rgb(t_texture *txtr, double u, double v);

// debug
unsigned int get_rgb_ui(t_texture *txtr, double u, double v);
# endif