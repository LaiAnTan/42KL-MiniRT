#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "mlx.h"

// mfw no M_PI
# define M_PI 3.14159265358979323846

// for idk what name is that emission
# define R_DEPTH 2

// settings
# define WIDTH 1280.0f
# define RAYS_IN_X 1280.0f
# define HEIGHT 720.0f
# define RAYS_IN_Y 720.0f

# define HORI_FOV 60.0f

# define AMBIENCE_FACTOR 0.2f
# define DIFFUSE_FACTOR 0.6f

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
	t_vector	*color;

	struct	s_light	*next;
} t_light;

typedef struct	s_circle
{
	double		radius;
} t_circle;

typedef struct	s_cam
{
	t_vector	*position;
	t_vector	*orientation;

	float		i_dont_know_how_to_deal_with_fovs;
} t_cam;

typedef struct	s_ambient
{
	t_vector	*color;
}	t_ambient;

typedef struct	s_plane
{
	t_vector	*normal_vect;
}	t_plane;

// because 10 linked list is painful
# define CIRCLE 0
# define PLANE 1

typedef	struct	s_objects
{
	int			type;
	t_vector	*position;
	t_vector	*color;

	t_circle	*circle;
	t_plane		*plane;

	struct s_objects	*next;
} t_objects;

typedef	struct	s_scene
{

	t_cam		*camera;
	t_objects	*objs;
	t_light		*lights;
	t_ambient	*ambient;

} t_scene;

void		kewl_quirky_raytrace(t_scene *scene, t_mlx_info *mlx);
void		calculate_ray_positions(double store[3], double x, double y);
t_ray		*project_ray(double x, double y, t_cam *camera);
void		do_ray_stuff(double x, double y, t_scene *scene, t_mlx_info *mlx);

t_circle	*init_circle(int r);
t_objects	*init_object(int type, double *pos, double *rgb);
t_plane		*init_plane(double *normal);
t_cam		*init_cam(int x, int y, int z);
t_light		*init_light(int x, int y, int z, t_matrix_type *color);
t_ambient	*init_ambient(int r, int g, int b, double a_strength);

void		free_circle(t_circle **c);
void		free_cam(t_cam **cam);
void		free_light(t_light **l);
void		free_objects(t_objects	**obj);
void		free_ambient(t_ambient **a);

void		get_image(t_img_info *img_info, void *mlx);
void		clean_loop(t_mlx_info *mlx);
void		write_pixel(t_img_info *img, int x, int y, int color);
int			create_trgb(t_vector *color);

double		intersect_plane(t_ray *ray, t_objects *o);
double		intersect_circle(t_ray	*ray, t_objects *o);

void		ambient_color(t_ray	*ray, t_ambient *a, t_objects *o);
t_vector	*inverse_color(t_vector	*c);
void		shadow_diffuse(t_ray *ray);
void		diffuse_the_bomb(t_ray *r, t_light *l, t_objects *o);
void		calculate_result_color(t_ray *r);

t_objects	*get_closest_object(t_ray *ray, t_scene *scene, int closest, double	*k_val);
int			get_closest_light(t_ray *r, t_light *l, t_scene *scene);

void		set_the_scene(t_scene *scene, double x);

double		abs_double(double val);
double		to_radian(double degree);
double		to_degree(double rad);

#endif