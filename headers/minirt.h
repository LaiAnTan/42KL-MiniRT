# pragma once

# ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define SUCCESS 1;
# define FAILURE 0;
# define ERROR -1;

typedef struct s_ambient
{
	int					a_rgb[3];

	float				a_ratio;

	struct s_ambient	*next;
}			t_ambient;

typedef struct s_camera
{
	int					cam_fov;

	float				cam_coords[3];
	float				cam_vec_orient[3];

	struct s_camera		*next;
}			t_camera;

typedef struct s_light
{
	int					l_rgb[3];

	float				l_coords[3];
	float				l_brightness;

	struct s_light		*next;
}			t_light;

typedef struct s_sphere
{
	int					sp_rgb[3];

	float				sp_diameter;
	float				sp_coords[3];

	struct s_sphere		*next;
}			t_sphere;

typedef struct s_plane
{
	int					pl_rgb[3];

	float				pl_coords[3];
	float				pl_vec_normal[3];

	struct s_plane		*next;
}			t_plane;

typedef struct s_cylinder
{
	int					cy_rgb[3];

	float				cy_height;
	float				cy_diameter;
	float				cy_coords[3];
	float				cy_vec_axis[3];

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

t_ambient	*scene_new_ambient(int a_rgb[3], float a_ratio);
t_camera	*scene_new_camera(int cam_fov, float cam_coords[3], float cam_vec_orient[3]);
t_light		*scene_new_light(int l_rgb[3], float l_coords[3], float l_brightness);
t_sphere	*scene_new_sphere(int sp_rgb[3], float sp_diameter, float sp_coords[3]);
t_plane		*scene_new_plane(int pl_rgb[3], float pl_coords[3], float pl_vec_normal[3]);
t_cylinder	*scene_new_cylinder(int cy_rgb[3], float cy_height, float cy_diameter, float cy_coords[3], float cy_vec_axis[3]);

# endif