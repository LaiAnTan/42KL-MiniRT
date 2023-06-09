#include "../headers/minirt.h"

t_ambient	*scene_new_ambient(double a_rgb[3], double a_ratio)
{
	matrix_type	black[3] = {255,255,255};
	t_vec3		*store;
	t_ambient	*new_ambient;

	new_ambient = (t_ambient *) malloc(sizeof(t_ambient));
	new_ambient->a_ratio = a_ratio;
	new_ambient->a_rgb = vec3_init_from_array(a_rgb);
	store = vec3_scalar_multi(new_ambient->a_rgb, (double) 1/255);
	new_ambient->a_strength = vec3_scalar_multi(store, a_ratio);
	vec3_free(&store);
	store = vec3_init_from_array(black);
	new_ambient->bg_color = vec3_multi_each_elem(store, new_ambient->a_strength);
	vec3_free(&store);
	return (new_ambient);
}

t_camera	*scene_new_camera(double cam_fov, double cam_coords[3], double cam_vec_orient[3])
{
	t_camera	*new_camera;
	t_vec3		*stuff;

	new_camera = (t_camera *) malloc(sizeof(t_camera));
	new_camera->cam_fov = cam_fov;
	new_camera->cam_coords = vec3_init_from_array(cam_coords);
	stuff = vec3_init_from_array(cam_vec_orient);
	new_camera->cam_vec_orient = vec3_normalize(stuff);
	vec3_free(&stuff);
	new_camera->cam_coords_v4 = NULL;
	new_camera->cam_vec_orient_v4 = NULL;
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
	object->next = NULL;
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

t_object	*scene_new_object(int ob_type, matrix_type *ob_coord, matrix_type *ob_rgb, double specular)
{
	t_object	*new_object;

	new_object = object_init();
	new_object->ob_type = ob_type;
	new_object->ob_coords = vec3_init_from_array(ob_coord);
	new_object->ob_rgb = vec3_init_from_array(ob_rgb);
	new_object->ob_spec = specular;
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
	t_vec3		*stuff;

	new_plane = (t_plane *) malloc(sizeof(t_plane));
	stuff = vec3_init_from_array(pl_vec_normal);
	new_plane->pl_vec_normal = vec3_normalize(stuff);
	vec3_free(&stuff);
	new_plane->pl_vec_normal_v4 = NULL;
	return (new_plane);
}

t_cylinder	*object_new_cylinder(double cy_height, double cy_diameter, double cy_vec_axis[3])
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	new_cylinder->cy_height = cy_height;
	new_cylinder->cy_diameter = cy_diameter;
	t_vec3	*temp;
	temp = vec3_init_from_array(cy_vec_axis);
	new_cylinder->cy_vec_axis = vec3_normalize(temp);
	vec3_free(&temp);
	return (new_cylinder);
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
		free(curr->l_rgb);
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
	free(cylinder);
}

// damn lazy check type lah
void	object_free_node(t_object *obj)
{
	vec3_free(&obj->ob_coords);
	vec3_free(&obj->ob_rgb);
	object_free_cylinder(obj->ob_cylinders);
	object_free_plane(obj->ob_planes);
	object_free_sphere(obj->ob_spheres);
	free(obj);
}

void	scene_free_object_list(t_object	*object_list_head)
{
	t_object	*temp;
	t_object	*curr;

	curr = object_list_head;
	while (curr)
	{
		temp = curr->next;
		object_free_node(curr);
		curr = temp;
	}
}

void	scene_free(t_scene *scene)
{
	if (scene->sc_ambients)
		scene_free_ambient(scene->sc_ambients);
	if (scene->sc_cameras)
		scene_free_camera_list(scene->sc_cameras);
	if (scene->sc_lights)
		scene_free_light_list(scene->sc_lights);
	if (scene->sc_objs)
		scene_free_object_list(scene->sc_objs);
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

// Debug

void	scene_print_ambient_stats(t_ambient *ambient)
{
	printf("a_ratio = %f\n", ambient->a_ratio);
	printf("a_rgb = ");
	vec3_print(ambient->a_rgb);
	printf("a_strength = ");
	vec3_print(ambient->a_strength);
	// printf("a_rgb = %d,%d,%d\n", ambient->a_rgb[0], ambient->a_rgb[1], ambient->a_rgb[2]);
}

void	scene_print_camera_stats(t_camera *camera)
{
	printf("cam_coords = ");
	vec3_print(camera->cam_coords);
	printf("cam_vec_orient = ");
	vec3_print(camera->cam_vec_orient);
	printf("cam_fov = %f\n", camera->cam_fov);
}

void	scene_print_light_stats(t_light *light)
{
	printf("l_coords = ");
	vec3_print(light->l_coords);
	printf("l_rgb = ");
	vec3_print(light->l_rgb);
	printf("l_brightness = %f\n", light->l_brightness);
}

void	scene_print_sphere_stats(t_sphere *sphere)
{
	printf("sp_diameter = %f\n", sphere->sp_diameter);
}

void	scene_print_plane_stats(t_plane *plane)
{
	printf("pl_vec_normal = ");
	vec3_print(plane->pl_vec_normal);
}

void	scene_print_cylinder_stats(t_cylinder *cylinder)
{
	printf("cy_vec_axis = ");
	vec3_print(cylinder->cy_vec_axis);
	printf("cy_diameter = %f\n", cylinder->cy_diameter);
	printf("cy_height = %f\n", cylinder->cy_height);
}

void	scene_print_object_stats(t_object *obj)
{
	printf("obj_coord =");
	vec3_print(obj->ob_coords);
	printf("obj_rgb =");
	vec3_print(obj->ob_rgb);
	printf("obj_specular = %f\n", obj->ob_spec);
	printf("obj_type = %d\n", obj->ob_type);
	if (obj->ob_cylinders)
		scene_print_cylinder_stats(obj->ob_cylinders);
	if (obj->ob_planes)
		scene_print_plane_stats(obj->ob_planes);
	if (obj->ob_spheres)
		scene_print_sphere_stats(obj->ob_spheres);
}

void	scene_print_stats(t_scene *scene)
{
	t_ambient *curr_ambient;
	t_camera *curr_camera;
	t_light *curr_light;
	t_object *curr_object;

	curr_ambient = scene->sc_ambients;
	curr_camera = scene->sc_cameras;
	curr_light = scene->sc_lights;
	curr_object = scene->sc_objs;
	printf("--ambients--\n");
	scene_print_ambient_stats(curr_ambient);
	printf("next\n");
	printf("--cameras--\n");
	while (curr_camera != NULL)
	{
		scene_print_camera_stats(curr_camera);
		curr_camera = curr_camera->next;
		printf("next\n");
	}
	printf("--lights--\n");
	while (curr_light != NULL)
	{
		scene_print_light_stats(curr_light);
		curr_light = curr_light->next;
		printf("next\n");
	}
	printf("--objects--\n");
	while (curr_object != NULL)
	{
		scene_print_object_stats(curr_object);
		curr_object = curr_object->next;
		printf("next\n");
	}
	printf("done\n");
}

