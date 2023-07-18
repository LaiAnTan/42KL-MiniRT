# pragma once

# ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

#if __linux__
	# include <X11/X.h>
	# include "../mlx_linux/mlx.h"
#elif __APPLE__
	# include <mlx.h>
#endif

# include "ray.h"
# include "matrix.h"
# include "vec3.h"
# include "vec4.h"
# include "timer.h"

/* Constants */
# define PI 3.14159265358979323846

/* get_next_line attributes */
# define BUFFER_SIZE 100

/* raytracing attributes */
# define WIDTH 1280.0f
# define RAYS_IN_X 1280.0f
# define HEIGHT 720.0f
# define RAYS_IN_Y 720.0f

# define AMBIENCE_FACTOR 0.2f
# define DIFFUSE_FACTOR 0.6f

/* codes */
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

typedef struct	s_img_info
{
	void	*img;

	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	*addr;
}			t_img_info;

typedef struct	s_mlx_info
{
	void	*mlx;
	void	*mlx_win;

	t_img_info	img;
}			t_mlx_info;

typedef struct s_ambient
{
	t_vec3				*a_rgb;
	// google can go suck my dick
	t_vec3				*a_strength;
	t_vec3				*bg_color;

	double				a_ratio;
}			t_ambient;

typedef struct s_camera
{
	double			cam_fov;

	t_vec3			*cam_coords;
	t_vec3			*cam_vec_orient;
	t_vec4			*cam_coords_v4;
	t_vec4			*cam_vec_orient_v4;

	// use on orientation vectors
	t_matrix		*orr_matrix;
	// use on points
	t_matrix		*view_matrix; // 4x4 view matrix that converts world coordinates -> view coordinates
	struct s_camera	*next;
}			t_camera;

typedef struct s_light
{
	double			l_brightness;

	t_vec3			*l_rgb;
	t_vec3			*l_coords;

	struct s_light	*next;
}			t_light;

typedef struct s_sphere
{
	double				sp_diameter;
	double				sp_radius;
}			t_sphere;

typedef struct s_plane
{
	t_vec3			*pl_vec_normal;
	t_vec4			*pl_vec_normal_v4;
}			t_plane;

typedef struct s_cylinder
{
	double			cy_height;
	double			cy_diameter;

	t_vec3			*cy_vec_axis;
	t_vec3			*cy_bottom;
}			t_cylinder;

typedef struct s_cone
{
	double			cn_height;
	double			cn_diameter;

	t_vec3			*cn_vec_axis;
	t_vec3			*cn_bottom;
}			t_cone;

// because 10 linked list is painful
# define CIRCLE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3
typedef struct s_object
{
	int				ob_type;
	t_sphere		*ob_spheres;
	t_plane			*ob_planes;
	t_cylinder		*ob_cylinders;
	t_cone			*ob_cones;

	double			ob_spec;
	t_vec3			*ob_coords;
	t_vec3			*ob_rgb;
	struct s_object	*next;
}		t_object;

typedef struct s_scene
{
	t_ambient		*sc_ambients;
	t_camera		*sc_cameras;
	t_light			*sc_lights;
	t_object		*sc_objs;
}			t_scene;

typedef struct s_data
{
	t_mlx_info		*mlx;
	t_scene			*scene;
}			t_data;

/* Scene Objects Boilerplate */

t_scene	*scene_init(void);

t_ambient	*scene_new_ambient(double a_rgb[3], double a_ratio);
t_camera	*scene_new_camera(double cam_fov, double cam_coords[3], double cam_vec_orient[3]);

t_object	*scene_new_object(int ob_type, matrix_type *ob_coord, matrix_type *ob_rgb, double specular);
t_light		*scene_new_light(double l_rgb[3], double l_coords[3], double l_brightness);

t_object	*object_init();
t_sphere	*object_new_sphere(double sp_diameter);
t_plane		*object_new_plane(double pl_vec_normal[3]);
t_cylinder	*object_new_cylinder(t_vec3 *center, double cy_height, double cy_diameter, double cy_vec_axis[3]);
t_cone		*object_new_cone(t_vec3 *center, double cn_height, double cn_diameter, double cn_vec_axis[3]);

void	scene_camera_add_back(t_camera **list_camera, t_camera *new_camera);
void	scene_light_add_back(t_light **list_light, t_light *new_light);
void	scene_object_add_back(t_object **list_object, t_object *new_object);

void	scene_free(t_scene *scene);
void	scene_free_ambient(t_ambient *ambient_list_head);
void	scene_free_camera_list(t_camera *camera_list_head);
void	scene_free_light_list(t_light *light_list_head);
void	scene_free_object_list(t_object	*object_list_head);

void	object_free_node(t_object *obj);
void	object_free_sphere(t_sphere *sphere);
void	object_free_plane(t_plane *plane);
void	object_free_cylinder(t_cylinder *cylinder);

// debug
void	scene_print_stats(t_scene *scene);

/* File Parsing */

t_scene	*file_create_scene(char *filename);

/* MLX */
void	get_image(t_img_info *img_info, void *mlx);
void	clean_loop(t_mlx_info *mlx);
void	write_pixel(t_img_info *img, int x, int y, int color);
void	mlx_free(t_mlx_info *mlx);

/* Events */
int	keypress_event(int key_symbol, t_data *data);

/* Utils */

void	copy_double_arr(double *copy_from, double *copy_to, int size);

int		ft_atoi(char *str);
int		count_2d_array(char **e);
int		is_digit(char *str);
int		is_valid(char *str);
int		ft_strcmp(char *s1, char *s2);

float	ft_atof(char *str);

size_t	ft_strlen(char *str);

char	*get_next_line(int fd);
char	*ft_append(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_substr(char *s, unsigned int start, unsigned int end);

char	**ft_split(char *s, char c);

double	absolute(double val);
double	to_radian(double degree);
double	to_degree(double rad);

void	free_2d_array(char **arr);

// --------------------------- uhhh have fun seperating ------------------------- //

void		calculate_ray_positions(double store[3], double x, double y, double fov);
t_ray		*project_ray(double x, double y, t_camera *camera);
void		do_ray_stuff(double x, double y, t_scene *scene, t_mlx_info *mlx);

int			create_trgb(t_vec3 *color);

void		raytrace(t_scene *scene, t_mlx_info *mlx);

double		intersect_plane(t_ray *ray, t_object *o);
double		intersect_circle(t_ray	*ray, t_object *o);
double		intersect_cylinder(t_ray *ray, t_object *o);
double		intersect_cone(t_ray *ray, t_object *o);

void		ambient_color(t_ray	*ray, t_ambient *a, t_object *o);
t_vec3		*inverse_color(t_vec3	*c);
void		shadow_diffuse(t_ray *ray);
void		diffuse_the_bomb(t_ray *r, t_light *l, t_object *o);
void		calculate_result_color(t_ray *r);

t_object	*get_closest_object(t_ray *ray, t_scene *scene, int closest, double	*k_val);
int			get_closest_light(t_ray *r, t_light *l, t_scene *scene);

// hm
void	cam_view_matrix(t_camera *cam);
void	change_to_view_port(t_scene *scn);

void	solve_quad(double *coefficients, double *result);

t_matrix	*construct_rotation(t_vec3 *right, t_vec3 *true_up, t_vec3 *forward);
t_vec3		*calc_cylinder_norm(t_ray *r, t_object *o);
t_vec3		*calc_cone_norm(t_ray *r, t_object *o);

void	swap(double *a, double *b);

# endif