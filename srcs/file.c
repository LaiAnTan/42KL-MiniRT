/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:22 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/05 18:28:44 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

// unpacks a string of 3 values (255,255,255) into an array of integers of size 3
// tokens is a 2d array aso.... (leaky)
double		*unpack_3_int_values(char *values)
{
	int		i;
	double		*unpacked;
	char	**tokens;

	i = 0;
	tokens = ft_split(values, ',');
	if (!tokens)
		return (NULL);
	else if (count_2d_array(tokens) > 3)
	{
		free_2d_array(tokens);
		return (NULL);
	}
	unpacked = (double *) malloc(sizeof(double) * 3);
	while (i < 3)
	{
		if (is_digit(tokens[i]) == 0)
		{
			free_2d_array(tokens);
			free(unpacked);
			return (NULL);
		}
		unpacked[i] = ft_atoi(tokens[i]);
		++i;
	}
	free_2d_array(tokens);
	return (unpacked);
}

// unpacks a string of 3 values (1.0,2.3,3.21) into an array of doubles of size 3
// tokens a 2d array (leak)
double	*unpack_3_double_values(char *values)
{
	int		i;
	double	*unpacked;
	char	**tokens;


	i = 0;
	tokens = ft_split(values, ',');
	if (!tokens)
		return (NULL);
	else if (count_2d_array(tokens) > 3)
	{
		free_2d_array(tokens);
		return (NULL);
	}
	unpacked = (double *) malloc(sizeof(double) * 3);
	while (i < 3)
	{
		if (is_valid(tokens[i]) == 0)
		{
			free_2d_array(tokens);
			free(unpacked);
			return (NULL);
		}
		unpacked[i] = (double) ft_atof(tokens[i]);
		++i;
	}
	free_2d_array(tokens);
	return (unpacked);
}

// checks if the string is a valid string of 3 values (255,255,255)
// values is a 2d array.... (leak)
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
	{
		free_2d_array(values);
		return (0);
	}
	while (values[i])
	{
		if (is_digit(values[i]) == 0 && is_valid(values[i]) == 0)
		{
			free_2d_array(values);
			return (0);
		}
		++i;
	}
	free_2d_array(values);
	return (1);
}

int	handle_object_ambient(t_scene *scene, char **tokens)
{
	double			*a_rgb;

	printf("found ambient object\n");
	if (count_2d_array(tokens) != 3)
		return (-1);
	if (is_valid_3_values(tokens[2]) == 0)
		return (-1);
	a_rgb = unpack_3_int_values(tokens[2]);
	if (!a_rgb)
		return (-1);
	scene->sc_ambients = scene_new_ambient(a_rgb, ft_atof(tokens[1]));
	free(a_rgb);
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
	free(cam_coords);
	free(cam_vec_orient);
	return (0);
}

int	handle_object_light(t_scene *scene, char **tokens)
{
	double		*l_rgb;
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
	new_light = scene_new_light(l_rgb, l_coords, atof(tokens[2]));
	scene_light_add_back(&scene->sc_lights, new_light);
	free(l_rgb);
	free(l_coords);
	return (0);
}

int	handle_object_sphere(t_scene *scene, char **tokens)
{
	double		*sp_rgb;
	double		*sp_coords;
	t_object	*new_object;

	printf("found sphere object\n");
	if (count_2d_array(tokens) != 6)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	sp_rgb = unpack_3_int_values(tokens[3]);
	sp_coords = unpack_3_double_values(tokens[1]);
	if (!sp_rgb || !sp_coords)
		return (-1);
	new_object = scene_new_object(CIRCLE, sp_coords, sp_rgb, ft_atof(tokens[4]), tokens[5]);
	new_object->ob_spheres = object_new_sphere((double) ft_atof(tokens[2]));
	scene_object_add_back(&scene->sc_objs, new_object);
	free(sp_rgb);
	free(sp_coords);
	return (0);
}

int	handle_object_plane(t_scene *scene, char **tokens)
{
	double		*pl_rgb;
	double		*pl_coords;
	double		*pl_vec_normal;
	t_object	*new_object;

	printf("found plane object\n");
	if (count_2d_array(tokens) != 6)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[3]) == 0)
		return (-1);
	pl_rgb = unpack_3_int_values(tokens[3]);
	pl_coords = unpack_3_double_values(tokens[1]);
	pl_vec_normal = unpack_3_double_values(tokens[2]);
	if (!pl_rgb || !pl_coords || !pl_vec_normal)
		return (-1);
	new_object = scene_new_object(PLANE, pl_coords, pl_rgb,  ft_atof(tokens[4]), tokens[5]);
	new_object->ob_planes = object_new_plane(pl_vec_normal);
	scene_object_add_back(&scene->sc_objs, new_object);
	free(pl_rgb);
	free(pl_coords);
	free(pl_vec_normal);
	return (0);
}

int	handle_object_cylinder(t_scene *scene, char **tokens)
{
	double		*cy_rgb;
	double		*cy_coords;
	double		*cy_vec_axis;
	t_object	*new_object;

	printf("found cylinder object\n");
	if (count_2d_array(tokens) != 8)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[5]) == 0)
		return (-1);
	cy_rgb = unpack_3_int_values(tokens[5]);
	cy_coords = unpack_3_double_values(tokens[1]);
	cy_vec_axis = unpack_3_double_values(tokens[2]);
	if (!cy_rgb || !cy_coords || !cy_vec_axis)
		return (-1);
	new_object = scene_new_object(CYLINDER, cy_coords, cy_rgb, ft_atof(tokens[6]), ft_strdup(tokens[7]));
	new_object->ob_cylinders = object_new_cylinder(new_object->ob_coords, (double) ft_atof(tokens[4]), (double) ft_atof(tokens[3]), cy_vec_axis);
	scene_object_add_back(&scene->sc_objs, new_object);
	free(cy_rgb);
	free(cy_coords);
	free(cy_vec_axis);
	return (0);
}

int	handle_object_cone(t_scene *scene, char **tokens)
{
	double		*cn_rgb;
	double		*cn_coords;
	double		*cn_vec_axis;
	t_object	*new_object;

	printf("found cone object\n");
	if (count_2d_array(tokens) != 8)
		return (-1);
	if (is_valid_3_values(tokens[1]) == 0 || is_valid_3_values(tokens[2]) == 0 || is_valid_3_values(tokens[5]) == 0)
		return (-1);
	cn_rgb = unpack_3_int_values(tokens[5]);
	cn_coords = unpack_3_double_values(tokens[1]);
	cn_vec_axis = unpack_3_double_values(tokens[2]);
	if (!cn_rgb || !cn_coords || !cn_vec_axis)
		return (-1);
	new_object = scene_new_object(CONE, cn_coords, cn_rgb, ft_atof(tokens[6]), tokens[7]);
	new_object->ob_cones = object_new_cone(new_object->ob_coords, (double) ft_atof(tokens[4]), (double) ft_atof(tokens[3]), cn_vec_axis);
	scene_object_add_back(&scene->sc_objs, new_object);
	free(cn_rgb);
	free(cn_coords);
	free(cn_vec_axis);
	return (0);
}

// ten points to who who managed to guess where leaked
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
	else if (ft_strcmp("cn", tokens[0]) == 0)
		error = handle_object_cone(scene, tokens);
	free_2d_array(tokens);
	if (error)
		return (error);
	return (0);
}

void	strip_nl(char **str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if ((*str)[len - 1] != '\n')
		return ;
	new_str = (char *) malloc (sizeof(char) * ft_strlen(*str));
	while (i < len - 1)
	{
		new_str[i] = (*str)[i]; // i fucking hate this
		++i;
	}
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
}

t_scene	*file_create_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	*new_scene;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("file not found\n");
		return (NULL);
	}
	line = NULL;
	new_scene = scene_init();
	while (1)
	{
		line = get_next_line(fd);
		strip_nl(&line);
		if (!line)
			break ;
		if (parse_line(new_scene, line))
		{
			printf("error in file configuration at line = %s\n", line);
			scene_free(new_scene, NULL);
			exit(0);
		}
		free(line);
	}
	printf("done parsing file\n");
	return (new_scene);
}