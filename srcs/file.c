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
		if (is_digit(tokens[i]) == 0)
		{
			free(tokens);
			free(unpacked);
			return (NULL);
		}
		unpacked[i] = ft_atoi(tokens[i]);
		++i;
	}
	return (unpacked);
}

// unpacks a string of 3 values (1.0,2.3,3.21) into an array of doubles of size 3
double	*unpack_3_double_values(char *values)
{
	int		i;
	double	*unpacked;
	char	**tokens;


	i = 0;
	tokens = ft_split(values, ',');
	if (!tokens || count_2d_array(tokens) > 3)
		return (NULL);
	unpacked = (double *) malloc(sizeof(double) * 3);
	while (i < 3)
	{
		if (is_decimal(tokens[i]) == 0)
		{
			free(tokens);
			free(unpacked);
			return (NULL);
		}
		unpacked[i] = (double) ft_atof(tokens[i]);
		++i;
	}
	free(tokens);
	return (unpacked);
}

/*
potential errors

wrong number of args
wrong format of args


todo: error handling for all handle_ functions
todo: change storage to double to prevent overflow in future
*/

// checks if the string is a valid string of 3 values (255,255,255)
int	is_valid_3_values(char *str)
{
	int	comma_count;
	int	decimal_count;

	comma_count = 0;
	decimal_count = 0;
	while (*str != '\0')
	{
		if (*str == ',')
		{
			decimal_count = 0;
			++comma_count;
		}
		else if (*str < '0' || *str > '9')
			return (0);
		else if (*str == '.')
			++decimal_count;
		if (decimal_count > 1)
			return (0);
		++str;
	}
	if (comma_count != 2)
		return (0);
	return (1);
}

int	handle_object_ambient(t_scene *scene, char **tokens)
{
	int			*a_rgb;
	t_ambient	*new_ambient;

	if (count_2d_array(tokens) != 3)
		return (-1);
	if (is_valid_3_values(tokens[2]) == 0)
		return (-1);
	a_rgb = unpack_3_int_values(tokens[2]);
	if (!a_rgb)
		return (-1);
	new_ambient = scene_new_ambient(a_rgb, ft_atof(tokens[1]));
	scene_ambient_add_back(&scene->sc_ambients, new_ambient);
	return (0);
}

int	handle_object_camera(t_scene *scene, char **tokens)
{
	double		*cam_coords;
	double		*cam_vec_orient;
	t_camera	*new_camera;

	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0)
		return (-1);
	cam_coords = unpack_3_double_values(tokens[1]);
	cam_vec_orient = unpack_3_double_values(tokens[2]);
	if (!cam_coords || !cam_vec_orient)
		return (-1);
	new_camera = scene_new_camera(ft_atoi(tokens[3]), cam_coords, cam_vec_orient);
	scene_camera_add_back(&scene->sc_cameras, new_camera);
	return (0);
}

int	handle_object_light(t_scene *scene, char **tokens)
{
	int			*l_rgb;
	double		*l_coords;
	t_light		*new_light;

	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	l_rgb = unpack_3_int_values(tokens[3]);
	l_coords = unpack_3_double_values(tokens[1]);
	if (!l_rgb || !l_coords)
		return (-1);
	new_light = scene_new_light(l_rgb, l_coords, (double) ft_atof(tokens[2]));
	scene_light_add_back(&scene->sc_lights, new_light);
	return (0);
}

int	handle_object_sphere(t_scene *scene, char **tokens)
{
	int			*sp_rgb;
	double		*sp_coords;
	t_sphere	*new_sphere;

	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	sp_rgb = unpack_3_double_values(tokens[3]);
	sp_coords = unpack_3_double_values(tokens[1]);
	if (!sp_rgb || !sp_coords)
		return (-1);
	new_sphere = scene_new_sphere(sp_rgb, (double) ft_atof(tokens[2]), sp_coords);
	scene_sphere_add_back(&scene->sc_spheres, new_sphere);
	return (0);
}

int	handle_object_plane(t_scene *scene, char **tokens)
{
	int			*pl_rgb;
	double		*pl_coords;
	double		*pl_vec_normal;
	t_plane		*new_plane;

	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	pl_rgb = unpack_3_int_values(tokens[3]);
	pl_coords = unpack_3_double_values(tokens[1]);
	pl_vec_normal = unpack_3_double_values(tokens[2]);
	if (!pl_rgb || !pl_coords || !pl_vec_normal)
		return (-1);
	new_plane = scene_new_plane(pl_rgb, pl_coords, pl_vec_normal);
	scene_plane_add_back(&scene->sc_planes, new_plane);
	return (0);
}

int	handle_object_cylinder(t_scene *scene, char **tokens)
{
	int			*cy_rgb;
	double		*cy_coords;
	double		*cy_vec_axis;
	t_cylinder	*new_cylinder;

	if (count_2d_array(tokens) != 6)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[5]) == 0)
		return (-1);
	cy_rgb = unpack_3_int_values(tokens[5]);
	cy_coords = unpack_3_double_values(tokens[1]);
	cy_vec_axis = unpack_3_double_values(tokens[2]);
	if (!cy_rgb || !cy_coords || !cy_vec_axis)
		return (-1);
	new_cylinder = scene_new_cylinder(cy_rgb, (double) ft_atof(tokens[4]), (double) ft_atof(tokens[3]), cy_coords, cy_vec_axis);
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
		else if (line[0] == '\n' && ft_strlen(line) == 1)
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