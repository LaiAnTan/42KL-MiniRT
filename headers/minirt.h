# pragma once

# ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define BUFFER_SIZE 100

typedef struct s_ambient
{
	int					a_rgb[3];

	double				a_ratio;

	struct s_ambient	*next;
}			t_ambient;

typedef struct s_camera
{
	int					cam_fov;

	double				cam_coords[3];
	double				cam_vec_orient[3];

	struct s_camera		*next;
}			t_camera;

typedef struct s_light
{
	int					l_rgb[3];

	double				l_coords[3];
	double				l_brightness;

	struct s_light		*next;
}			t_light;

typedef struct s_sphere
{
	int					sp_rgb[3];

	double				sp_diameter;
	double				sp_coords[3];

	struct s_sphere		*next;
}			t_sphere;

typedef struct s_plane
{
	int					pl_rgb[3];

	double				pl_coords[3];
	double				pl_vec_normal[3];

	struct s_plane		*next;
}			t_plane;

typedef struct s_cylinder
{
	int					cy_rgb[3];

	double				cy_height;
	double				cy_diameter;
	double				cy_coords[3];
	double				cy_vec_axis[3];

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
	t_scene		scene;
}			t_data;

/* Scene Objects Boilerplate */

t_ambient	*scene_new_ambient(int a_rgb[3], double a_ratio);
t_camera	*scene_new_camera(int cam_fov, double cam_coords[3], double cam_vec_orient[3]);
t_light		*scene_new_light(int l_rgb[3], double l_coords[3], double l_brightness);
t_sphere	*scene_new_sphere(int sp_rgb[3], double sp_diameter, double sp_coords[3]);
t_plane		*scene_new_plane(int pl_rgb[3], double pl_coords[3], double pl_vec_normal[3]);
t_cylinder	*scene_new_cylinder(int cy_rgb[3], double cy_height, double cy_diameter, double cy_coords[3], double cy_vec_axis[3]);

void	scene_ambient_add_back(t_ambient **list_ambient, t_ambient *new_ambient);
void	scene_camera_add_back(t_camera **list_camera, t_camera *new_camera);
void	scene_light_add_back(t_light **list_light, t_light *new_light);
void	scene_sphere_add_back(t_sphere **list_sphere, t_sphere *new_sphere);
void	scene_plane_add_back(t_plane **list_plane, t_plane *new_plane);
void	scene_cylinder_add_back(t_cylinder **list_cylinder, t_cylinder *new_cylinder);

// debug
void	scene_print_stats(t_scene *scene);

/* File Parsing */

t_scene	*file_create_scene(char *filename);


/* Utils */

void	copy_int_arr(int *copy_from, int *copy_to, int size);
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