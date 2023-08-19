/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:32 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/19 19:11:04 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

t_ambient	*scene_new_ambient(double a_rgb[3], double a_ratio)
{
	t_ambient	*new_ambient;

	new_ambient = (t_ambient *) malloc(sizeof(t_ambient));
	new_ambient->a_ratio = a_ratio;
	new_ambient->a_rgb = vec3_init_from_array(a_rgb);
	new_ambient->a_strength = vec3_scalar_multi(new_ambient->a_rgb, (double) 1/255, O_CREATE);
	vec3_scalar_multi(new_ambient->a_strength, a_ratio, O_REPLACE);
	new_ambient->bg_color = vec3_multi_each_elem(vec3_init(255,255,255), new_ambient->a_strength, O_REPLACE);
	return (new_ambient);
}

t_camera	*scene_new_camera(double cam_fov, double cam_coords[3], double cam_vec_orient[3])
{
	t_camera	*new_camera;

	new_camera = (t_camera *) malloc(sizeof(t_camera));
	new_camera->cam_fov = cam_fov;
	new_camera->cam_coords = vec3_init_from_array(cam_coords);
	new_camera->cam_vec_orient = vec3_normalize(vec3_init_from_array(cam_vec_orient), O_REPLACE);
	new_camera->cam_coords_v4 = NULL;
	new_camera->cam_vec_orient_v4 = NULL;
	new_camera->orr_matrix = NULL;
	new_camera->view_matrix = NULL;
	new_camera->next = NULL;
	return (new_camera);
}

t_light		*scene_new_light(double l_rgb[3], double l_coords[3], double l_brightness)
{
	t_light		*new_light;

	new_light = (t_light *) malloc(sizeof(t_light));
	new_light->l_rgb = vec3_init_from_array(l_rgb);
	new_light->l_coords = vec3_init_from_array(l_coords);
	new_light->l_brightness = l_brightness;
	new_light->next = NULL;
	return (new_light);
}

t_object	*object_init()
{
	t_object	*object;

	object = (t_object *) malloc(sizeof(t_object));
	object->ob_type = -1;
	object->ob_coords = NULL;
	object->ob_rgb = NULL;
	object->ob_spec = -1;
	object->ob_cylinders = NULL;
	object->ob_planes = NULL;
	object->ob_spheres = NULL;
	object->ob_cones = NULL;
	object->next = NULL;
	object->has_texture = NULL;
	object->ob_texture = NULL;
	return (object);
}

void	scene_object_add_back(t_object **list_object, t_object *new_object)
{
	t_object *curr_node;

	if (!new_object)
		return ;
	if (!*list_object)
	{
		*list_object = new_object;
		return ;
	}
	curr_node = *list_object;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_object;
}

/*               No switches?
** ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝
** ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇
** ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀
** ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀
** ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀
** ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀
** ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/

void	assign_function(t_object *new_object, int ob_type)
{
	object_runner	store[4];

	store[0] = intersect_circle;
	store[1] = intersect_plane;
	store[2] = intersect_cylinder;
	store[3] = intersect_cone;
	new_object->intersect_checker = store[ob_type];
}

t_object	*scene_new_object(int ob_type, matrix_type *ob_coord, matrix_type *ob_rgb, double specular, char *ob_tex_filename)
{
	t_object	*new_object;

	new_object = object_init();
	new_object->ob_type = ob_type;
	assign_function(new_object, ob_type);
	new_object->ob_coords = vec3_init_from_array(ob_coord);
	new_object->ob_rgb = vec3_init_from_array(ob_rgb);
	new_object->ob_spec = specular;
	if (ft_strcmp(ob_tex_filename, "none") != 0)
		new_object->has_texture = ft_strdup(ob_tex_filename);
	else
		new_object->has_texture = NULL;
	return (new_object);
}

t_sphere	*object_new_sphere(double sp_diameter)
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *) malloc(sizeof(t_sphere));
	new_sphere->sp_diameter = sp_diameter;
	new_sphere->sp_radius = sp_diameter / 2;
	return (new_sphere);
}

t_plane		*object_new_plane(double pl_vec_normal[3])
{
	t_plane		*new_plane;

	new_plane = (t_plane *) malloc(sizeof(t_plane));
	new_plane->pl_vec_normal = vec3_normalize(vec3_init_from_array(pl_vec_normal), O_REPLACE);
	new_plane->pl_vec_normal_v4 = NULL;
	return (new_plane);
}

t_cylinder	*object_new_cylinder(double cy_height, double cy_diameter, double cy_vec_axis[3])
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	new_cylinder->cy_height = cy_height;
	new_cylinder->cy_diameter = cy_diameter;
	new_cylinder->cy_vec_axis = vec3_normalize(vec3_init_from_array(cy_vec_axis), O_REPLACE);
	new_cylinder->cy_bottom = NULL;
	return (new_cylinder);
}

t_cone	*object_new_cone(double cn_height, double cn_diameter, double cn_vec_axis[3])
{
	t_cone	*new_cone; 
	
	new_cone = (t_cone *) malloc(sizeof(t_cone));
	new_cone->cn_height = cn_height;
	new_cone->cn_diameter = cn_diameter;
	new_cone->cn_vec_axis = vec3_normalize(vec3_init_from_array(cn_vec_axis), O_REPLACE);
	new_cone->cn_bottom = NULL;
	return (new_cone);
}

void	scene_camera_add_back(t_camera **list_camera, t_camera *new_camera)
{
	t_camera *curr_node;

	if (!new_camera)
		return ;
	if (!*list_camera)
	{
		*list_camera = new_camera;
		return ;
	}
	curr_node = *list_camera;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_camera;
}

void	scene_light_add_back(t_light **list_light, t_light *new_light)
{
	t_light *curr_node;

	if (!new_light)
		return ;
	if (!*list_light)
	{
		*list_light = new_light;
		return ;
	}
	curr_node = *list_light;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_light;
}

void	scene_free_ambient(t_ambient *ambient)
{
	if (ambient == NULL)
		return ;

	vec3_free(&ambient->a_rgb);
	vec3_free(&ambient->a_strength);
	vec3_free(&ambient->bg_color);
	free(ambient);
}

void	scene_free_camera_list(t_camera *camera_list_head)
{
	t_camera	*temp;
	t_camera	*curr;

	curr = camera_list_head;
	while (curr)
	{
		temp = curr->next;
		vec3_free(&curr->cam_coords);
		vec3_free(&curr->cam_vec_orient);
		vec4_free(&curr->cam_coords_v4);
		vec4_free(&curr->cam_vec_orient_v4);

		free_matrix(&curr->orr_matrix);
		free_matrix(&curr->view_matrix);

		free(curr);
		curr = temp;
	}
}

void	scene_free_light_list(t_light *light_list_head)
{
	t_light	*temp;
	t_light	*curr;

	curr = light_list_head;
	while (curr)
	{
		temp = curr->next;
		vec3_free(&curr->l_rgb);
		vec3_free(&curr->l_coords);
		free(curr);
		curr = temp;
	}
}

void	object_free_sphere(t_sphere *sphere)
{
	if (!sphere)
		return ;
	free(sphere);
}

void	object_free_plane(t_plane *plane)
{
	if (!plane)
		return ;
	vec3_free(&plane->pl_vec_normal);
	if (plane->pl_vec_normal_v4)
		vec4_free(&plane->pl_vec_normal_v4);
	free(plane);
}

void	object_free_cylinder(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	vec3_free(&cylinder->cy_vec_axis);
	vec3_free(&cylinder->cy_bottom);
	free(cylinder);
}

void	object_free_cone(t_cone *cone)
{
	if (!cone)
		return ;
	vec3_free(&cone->cn_vec_axis);
	vec3_free(&cone->cn_bottom);
	free(cone);
}

// damn lazy check type lah
void	object_free_node(t_object *obj, void *mlx)
{
	if (!obj)
		return
	vec3_free(&obj->ob_coords);
	vec3_free(&obj->ob_rgb);
	object_free_cylinder(obj->ob_cylinders);
	object_free_plane(obj->ob_planes);
	object_free_sphere(obj->ob_spheres);
	object_free_cone(obj->ob_cones);
	if (obj->has_texture)
	{
		free(obj->has_texture);
		if (mlx)
			free_texture(obj->ob_texture, mlx);
	}
	free(obj);
}

void	scene_free_object_list(t_object	*object_list_head, void *mlx_ptr)
{
	t_object	*temp;
	t_object	*curr;

	curr = object_list_head;
	while (curr)
	{
		temp = curr->next;
		object_free_node(curr, mlx_ptr);
		curr = temp;
	}
}

void	scene_free(t_scene *scene, void *mlx_ptr)
{
	if (!scene)
		return ;

	if (scene->sc_ambients)
		scene_free_ambient(scene->sc_ambients);
	if (scene->sc_cameras)
		scene_free_camera_list(scene->sc_cameras);
	if (scene->sc_lights)
		scene_free_light_list(scene->sc_lights);
	if (scene->sc_objs)
		scene_free_object_list(scene->sc_objs, mlx_ptr);
	free(scene);
}

t_scene	*scene_init(void)
{
	t_scene	*new_scene;

	new_scene = (t_scene *) malloc(sizeof(t_scene));
	new_scene->sc_ambients = NULL;
	new_scene->sc_lights = NULL;
	new_scene->sc_objs = NULL;
	new_scene->sc_cameras = NULL;
	return (new_scene);
}

void	get_texture_files(t_object *objs, void *mlx_ptr)
{
	while (objs)
	{
		if (objs->has_texture)
		{
			objs->ob_texture = texture_init(objs->has_texture, mlx_ptr);
			if (!objs->ob_texture)
				objs->has_texture = NULL;
		}
		objs = objs->next;
	}
}