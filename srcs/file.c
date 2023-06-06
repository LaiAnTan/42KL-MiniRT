# include "../headers/minirt.h"

// unpacks a string of 3 values (255,255,255) into an array of integers of size 3
int		*unpack_3_int_values(char *values)
{
	int		i;
	int		*unpacked;
	char	**tokens;

	i = 0;
	tokens = ft_split(values, ',');
	if (count_2d_array(tokens) > 3)
		return (NULL);
	unpacked = (int *) malloc(sizeof(int) * 3);
	while (i < 3)
	{
		unpacked[i] = ft_atoi(tokens[i]);
		++i;
	}
	return (unpacked);
}

// unpacks a string of 3 values (1.0,2.3,3.21) into an array of floats of size 3
float	*unpack_3_float_values(char *values)
{
	int		i;
	float	*unpacked;
	char	**tokens;


	i = 0;
	tokens = ft_split(values, ',');
	if (count_2d_array(tokens) > 3)
		return (NULL);
	unpacked = (float *) malloc(sizeof(float) * 3);
	while (i < 3)
	{
		unpacked[i] = ft_atof(tokens[i]);
		++i;
	}
	free(tokens);
	return (unpacked);
}

/*
--argument orders--
ambient ratio rgb
camera coords orient_vec fov
light coords brightness rgb
sphere coords diameter rgb
plane coords norm_vec rgb
cylinder coords axis_vec diameter height rgb
*/

int	handle_object_ambient(t_scene *scene, char **tokens)
{
	int			*a_rgb;
	t_ambient	*new_ambient;

	a_rgb = unpack_3_int_values(tokens[2]);
	if (!a_rgb)
		return (-1);
	new_ambient = scene_new_ambient(a_rgb, ft_atof(tokens[1]));
	scene_ambient_add_back(&scene->sc_ambients, new_ambient);
	return (0);
}

int	handle_object_camera(t_scene *scene, char **tokens)
{
	float		*cam_coords;
	float		*cam_vec_orient;
	t_camera	*new_camera;


	cam_coords = unpack_3_float_values(tokens[1]);
	cam_vec_orient = unpack_3_float_values(tokens[2]);
	if (!cam_coords || !cam_vec_orient)
		return (-1);
	new_camera = scene_new_camera(ft_atoi(tokens[3]), cam_coords, cam_vec_orient);
	scene_camera_add_back(&scene->sc_cameras, new_camera);
	return (0);
}

int	handle_object_light(t_scene *scene, char **tokens)
{
	int			*l_rgb;
	float		*l_coords;
	t_light		*new_light;

	l_rgb = unpack_3_int_values(tokens[3]);
	l_coords = unpack_3_float_values(tokens[1]);
	if (!l_rgb || !l_coords)
		return (-1);
	new_light = scene_new_light(l_rgb, l_coords, ft_atof(tokens[2]));
	scene_light_add_back(&scene->sc_lights, new_light);
	return (0);
}

int	handle_object_sphere(t_scene *scene, char **tokens)
{
	int			*sp_rgb;
	float		*sp_coords;
	t_sphere	*new_sphere;

	sp_rgb = unpack_3_int_values(tokens[3]);
	sp_coords = unpack_3_float_values(tokens[1]);
	if (!sp_rgb || !sp_coords)
		return (-1);
	new_sphere = scene_new_sphere(sp_rgb, ft_atof(tokens[2]), sp_coords);
	scene_sphere_add_back(&scene->sc_spheres, new_sphere);
	return (0);
}

int	handle_object_plane(t_scene *scene, char **tokens)
{
	int			*pl_rgb;
	float		*pl_coords;
	float		*pl_vec_normal;
	t_plane		*new_plane;

	pl_rgb = unpack_3_int_values(tokens[3]);
	pl_coords = unpack_3_float_values(tokens[1]);
	pl_vec_normal = unpack_3_float_values(tokens[2]);
	if (!pl_rgb || !pl_coords || !pl_vec_normal)
		return (-1);
	new_plane = scene_new_plane(pl_rgb, pl_coords, pl_vec_normal);
	scene_plane_add_back(&scene->sc_planes, new_plane);
	return (0);
}

int	handle_object_cylinder(t_scene *scene, char **tokens)
{
	int			*cy_rgb;
	float		*cy_coords;
	float		*cy_vec_axis;
	t_cylinder	*new_cylinder;

	cy_rgb = unpack_3_int_values(tokens[5]);
	cy_coords = unpack_3_float_values(tokens[1]);
	cy_vec_axis = unpack_3_float_values(tokens[2]);
	if (!cy_rgb || !cy_coords || !cy_vec_axis)
		return (-1);
	new_cylinder = scene_new_cylinder(cy_rgb, ft_atof(tokens[4]), ft_atof(tokens[3]), cy_coords, cy_vec_axis);
	scene_cylinder_add_back(&scene->sc_cylinders, new_cylinder);
	return (0);
}

int	parse_line(t_scene *scene, char *line)
{
	int		error;
	char	**tokens;

	error = 0;
	tokens = ft_split(line, ' ');
	if (ft_strcmp("A", tokens[0]) == 0)
		error = handle_object_ambient(scene, tokens);
	else if (ft_strcmp("C", tokens[0]) == 0)
		error = handle_object_camera(scene, tokens);
	else if (ft_strcmp("L", tokens[0]) == 0)
		error = handle_object_light(scene, tokens);
	else if (ft_strcmp("sp", tokens[0]) == 0)
		error = handle_object_sphere(scene, tokens);
	else if (ft_strcmp("pl", tokens[0]) == 0)
		error = handle_object_plane(scene, tokens);
	else if (ft_strcmp("cy", tokens[0]) == 0)
		error = handle_object_cylinder(scene, tokens);
	free(tokens);
	if (error)
		return (error);
	return (0);
}

t_scene	*file_create_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	*new_scene;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = NULL;
	new_scene = (t_scene *) malloc(sizeof(t_scene));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (line[0] = '\n' && ft_strlen(line) == 1)
			continue ;
		if (parse_line(new_scene, line))
		{
			printf("error in file configuration");
			exit(0);
		}
		free(line);
	}
	return (new_scene);
}