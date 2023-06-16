# include "../headers/minirt.h"

// unpacks a string of 3 values (255,255,255) into an array of integers of size 3
double		*unpack_3_int_values(char *values)
{
	int		i;
	double		*unpacked;
	char	**tokens;

	i = 0;
	tokens = ft_split(values, ',');
	if (count_2d_array(tokens) > 3)
		return (NULL);
	unpacked = (double *) malloc(sizeof(double) * 3);
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

// checks if the string is a valid string of 3 values (255,255,255)
int	is_valid_3_values(char *str)
{
	int		i;
	int		comma_count;
	char	**values;

	i = 0;
	comma_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			++comma_count;
		++i;
	}
	if (comma_count != 2)
		return (0);
	i = 0;
	values = ft_split(str, ',');
	if (count_2d_array(values) != 3)
		return (0);
	while (values[i])
	{
		// printf("checking = %s\n", values[i]);
		if (is_digit(values[i]) == 0 && is_decimal(values[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

int	handle_object_ambient(t_scene *scene, char **tokens)
{
	double			*a_rgb;
	t_ambient	*new_ambient;

	printf("found ambient object\n");
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

	printf("found camera object\n");
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
	double			*l_rgb;
	double		*l_coords;
	t_light		*new_light;

	printf("found light object\n");
	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	l_rgb = unpack_3_int_values(tokens[3]);
	l_coords = unpack_3_double_values(tokens[1]);
	if (!l_rgb || !l_coords)
		return (-1);
	new_light = scene_new_light(l_rgb, l_coords);
	scene_light_add_back(&scene->sc_lights, new_light);
	return (0);
}

int	handle_object_sphere(t_scene *scene, char **tokens)
{
	double		*sp_rgb;
	double		*sp_coords;
	t_object	*new_object;

	printf("found sphere object\n");
	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	sp_rgb = unpack_3_int_values(tokens[3]);
	sp_coords = unpack_3_double_values(tokens[1]);
	if (!sp_rgb || !sp_coords)
		return (-1);
	new_object = scene_new_object(CIRCLE, sp_coords, sp_rgb);
	new_object->ob_spheres = scene_new_sphere((double) ft_atof(tokens[2]));
	scene_object_add_back(&scene->sc_objs, new_object);
	// new_sphere = scene_new_sphere(sp_rgb, (double) ft_atof(tokens[2]), sp_coords);
	// scene_sphere_add_back(&scene->sc_spheres, new_sphere);
	return (0);
}

int	handle_object_plane(t_scene *scene, char **tokens)
{
	double		*pl_rgb;
	double		*pl_coords;
	double		*pl_vec_normal;
	t_object	*new_object;

	printf("found plane object\n");
	if (count_2d_array(tokens) != 4)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	pl_rgb = unpack_3_int_values(tokens[3]);
	pl_coords = unpack_3_double_values(tokens[1]);
	pl_vec_normal = unpack_3_double_values(tokens[2]);
	if (!pl_rgb || !pl_coords || !pl_vec_normal)
		return (-1);
	new_object = scene_new_object(PLANE, pl_coords, pl_rgb);
	new_object->ob_spheres = scene_plane_add_back(pl_vec_normal);
	scene_object_add_back(&scene->sc_objs, new_object);
	// new_plane = scene_new_plane(pl_rgb, pl_coords, pl_vec_normal);
	// scene_plane_add_back(&scene->sc_planes, new_plane);
	return (0);
}

int	handle_object_cylinder(t_scene *scene, char **tokens)
{
	double		*cy_rgb;
	double		*cy_coords;
	double		*cy_vec_axis;
	t_object	*new_object;

	printf("found cylinder object\n");
	if (count_2d_array(tokens) != 6)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[5]) == 0)
		return (-1);
	cy_rgb = unpack_3_int_values(tokens[5]);
	cy_coords = unpack_3_double_values(tokens[1]);
	cy_vec_axis = unpack_3_double_values(tokens[2]);
	if (!cy_rgb || !cy_coords || !cy_vec_axis)
		return (-1);
	new_object = scene_new_object(CIRCLE, cy_coords, cy_rgb);
	new_object->ob_spheres = scene_new_cylinder((double) ft_atof(tokens[4]), (double) ft_atof(tokens[3]), cy_vec_axis);
	scene_object_add_back(&scene->sc_objs, new_object);
	// new_cylinder = scene_new_cylinder(cy_rgb, (double) ft_atof(tokens[4]), (double) ft_atof(tokens[3]), cy_coords, cy_vec_axis);
	// scene_cylinder_add_back(&scene->sc_cylinders, new_cylinder);
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

char	*strip_nl(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = ft_strlen(str);
	if (!str)
		return (NULL);
	if (str[len - 1] != '\n')
		return (str);
	new_str = (char *) malloc (sizeof(char) * ft_strlen(str));
	while (i < len - 1)
	{
		new_str[i] = str[i];
		++i;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
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
	new_scene = scene_init();
	while (1)
	{
		line = strip_nl(get_next_line(fd));
		if (!line)
			break ;
		else if (line[0] == '\n' && ft_strlen(line) == 1)
			continue ;
		// printf("curr line = %s\n", line);
		if (parse_line(new_scene, line))
		{
			printf("error in file configuration\n");
			exit(0);
		}
		free(line);
	}
	printf("done parsing file\n");
	return (new_scene);
}