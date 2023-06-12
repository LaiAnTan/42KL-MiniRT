# pragma once

# ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "mlx.h"
# include "ray.h"
# include "matrix.h"
# include "vec3.h"
# include "vec4.h"

/* Constants */
# define PI 3.14159265358979323846

/* get_next_line attributes */
# define BUFFER_SIZE 100

/* raytracing attributes */
#define WIDTH 1280
#define HEIGHT 720

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

	double				a_ratio;

	struct s_ambient	*next;
}			t_ambient;

typedef struct s_camera
{
	int					cam_fov;

	t_vec4			*cam_coords;
	t_vec4			*cam_vec_orient;

	t_matrix		*view_matrix; // 4x4 view matrix that converts world coordinates -> view coordinates

	struct s_camera		*next;
}			t_camera;

typedef struct s_light
{
	t_vec3			*l_rgb;

	t_vec4			*l_coords;

	struct s_light		*next;
}			t_light;

typedef struct s_sphere
{
	t_vec3				*sp_rgb;

	double				sp_diameter;
	double				sp_radius;

	t_vec4			*sp_coords;

	struct s_sphere		*next;
}			t_sphere;

typedef struct s_plane
{
	t_vec3			*pl_rgb;

	t_vec4			*pl_coords;
	t_vec4			*pl_vec_normal;

	struct s_plane		*next;
}			t_plane;

typedef struct s_cylinder
{
	t_vec3			*cy_rgb;

	double			cy_height;
	double			cy_diameter;

	t_vec4			*cy_coords;
	t_vec4			*cy_vec_axis;

	struct s_cylinder	*next;
}			t_cylinder;

typedef struct s_scene
{
	t_ambient		*sc_ambients;
	t_camera		*sc_cameras;
	t_light			*sc_lights;
	t_sphere		*sc_spheres;
	t_plane			*sc_planes;
	t_cylinder		*sc_cylinders;
}			t_scene;

typedef struct s_data
{
	t_mlx_info		*mlx;
	t_scene			*scene;
}			t_data;

/* coordinate systems transformation matrices */
t_matrix	*get_view_matrix(t_vec3 *position, t_vec3 *reference, t_vec3 *up); // world-to-view matrix

t_matrix	*get_model_matrix(t_cylinder *cylinder); // model-to-world for cylinder

t_matrix	*get_inverse_transform(t_matrix *transform); // inverse for transformation matrices

t_vec4	*convert_pixels(int pixel_y, int pixel_x, t_camera *camera);

/* Scene Objects Boilerplate */

t_scene	*scene_init(void);

t_ambient	*scene_new_ambient(double a_rgb[3], double a_ratio);
t_camera	*scene_new_camera(int cam_fov, double cam_coords[3], double cam_vec_orient[3]);
t_light		*scene_new_light(double l_rgb[3], double l_coords[3]);
t_sphere	*scene_new_sphere(double sp_rgb[3], double sp_diameter, double sp_coords[3]);
t_plane		*scene_new_plane(double pl_rgb[3], double pl_coords[3], double pl_vec_normal[3]);
t_cylinder	*scene_new_cylinder(double cy_rgb[3], double cy_height, double cy_diameter, double cy_coords[3], double cy_vec_axis[3]);

void	scene_ambient_add_back(t_ambient **list_ambient, t_ambient *new_ambient);
void	scene_camera_add_back(t_camera **list_camera, t_camera *new_camera);
void	scene_light_add_back(t_light **list_light, t_light *new_light);
void	scene_sphere_add_back(t_sphere **list_sphere, t_sphere *new_sphere);
void	scene_plane_add_back(t_plane **list_plane, t_plane *new_plane);
void	scene_cylinder_add_back(t_cylinder **list_cylinder, t_cylinder *new_cylinder);

void	scene_free_ambient_list(t_ambient *ambient_list_head);
void	scene_free_camera_list(t_camera *camera_list_head);
void	scene_free_light_list(t_light *light_list_head);
void	scene_free_sphere_list(t_sphere *sphere_list_head);
void	scene_free_plane_list(t_plane *plane_list_head);
void	scene_free_cylinder_list(t_cylinder *cylinder_list_head);

void	scene_free_objects(t_scene *scene);

// debug
void	scene_print_stats(t_scene *scene);

/* File Parsing */

t_scene	*file_create_scene(char *filename);

/* MLX */
void	get_image(t_img_info *img_info, void *mlx);
void	clean_loop(t_mlx_info *mlx);
void	write_pixel(t_img_info *img, int x, int y, int color);

int		create_trgb(int r, int g, int b);

/* Utils */

void	copy_double_arr(double *copy_from, double *copy_to, int size);

int		ft_atoi(char *str);
int		count_2d_array(char **e);
int		is_digit(char *str);
int		is_decimal(char *str);
int		ft_strcmp(char *s1, char *s2);

float	ft_atof(char *str);

size_t	ft_strlen(char *str);

char	*get_next_line(int fd);
char	*ft_append(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_substr(char *s, unsigned int start, unsigned int end);

char	**ft_split(char *s, char c);

# endif