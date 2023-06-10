#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "mlx.h"

// mfw no M_PI
# define M_PI 3.14159265358979323846

// settings
# define WIDTH 600
# define HEIGHT 450

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

typedef struct	s_img_info {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_info;

typedef struct	s_mlx_info
{
	void	*mlx;
	void	*mlx_win;

	t_img_info	img;
} t_mlx_info;

typedef	struct	s_light
{
	t_vector	*position;
	int			color[3];

	struct	s_light	*next;
} t_light;

typedef struct	s_circle
{
	t_vector	*position;
	int			color[3];
	double		radius;

	struct s_circle	*next;
} t_circle;

typedef struct	s_cam
{
	t_vector	*position;
	t_vector	*orientation;

	float		i_dont_know_how_to_deal_with_fovs;
} t_cam;

typedef	struct	s_scene
{
	t_cam		*camera;
	t_circle	*circles;
	t_light		*lights;
} t_scene;


t_circle	*init_circle(int x, int y, int z, int r);
t_cam		*init_cam(int x, int y, int z);
t_light		*init_light(int x, int y, int z);

void	free_circle(t_circle *c);
void	free_cam(t_cam *cam);
void	free_light(t_light *l);

#endif