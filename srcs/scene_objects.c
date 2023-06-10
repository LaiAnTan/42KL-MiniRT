#include "../headers/minirt.h"

t_ambient	*scene_new_ambient(int a_rgb[3], double a_ratio)
{
	t_ambient	*new_ambient;

	new_ambient = (t_ambient *) malloc(sizeof(t_ambient));
	new_ambient->a_ratio = a_ratio;
	copy_int_arr(a_rgb, new_ambient->a_rgb, 3);
	
	new_ambient->next = NULL;
	return (new_ambient);
}

t_camera	*scene_new_camera(int cam_fov, double cam_coords[3], double cam_vec_orient[3])
{
	t_camera	*new_camera;

	new_camera = (t_camera *) malloc(sizeof(t_camera));
	new_camera->cam_fov = cam_fov;
	new_camera->cam_coords = vec_4_init_from_coordinates(cam_coords);
	new_camera->cam_vec_orient = vec_4_init_from_coordinates(cam_vec_orient);
	new_camera->view_matrix = NULL;
	new_camera->next = NULL;
	return (new_camera);
}

t_light		*scene_new_light(int l_rgb[3], double l_coords[3], double l_brightness)
{
	t_light		*new_light;

	new_light = (t_light *) malloc(sizeof(t_light));
	copy_int_arr(l_rgb, new_light->l_rgb, 3);
	new_light->l_coords = vec_4_init_from_coordinates(l_coords);
	new_light->l_brightness = l_brightness;
	new_light->next = NULL;
	return (new_light);
}

t_sphere	*scene_new_sphere(int sp_rgb[3], double sp_diameter, double sp_coords[3])
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *) malloc(sizeof(t_sphere));
	copy_int_arr(sp_rgb, new_sphere->sp_rgb, 3);
	new_sphere->sp_coords = vec_4_init_from_coordinates(sp_coords);
	new_sphere->sp_diameter = sp_diameter;
	new_sphere->sp_radius = sp_diameter / 2;
	new_sphere->next = NULL;
	return (new_sphere);
}

t_plane		*scene_new_plane(int pl_rgb[3], double pl_coords[3], double pl_vec_normal[3])
{
	t_plane		*new_plane;

	new_plane = (t_plane *) malloc(sizeof(t_plane));
	copy_int_arr(pl_rgb, new_plane->pl_rgb, 3);
	new_plane->pl_coords = vec_4_init_from_coordinates(pl_coords);
	new_plane->pl_vec_normal = vec_4_init_from_coordinates(pl_vec_normal);
	new_plane->next = NULL;
	return (new_plane);
}

t_cylinder	*scene_new_cylinder(int cy_rgb[3], double cy_height, double cy_diameter, double cy_coords[3], double cy_vec_axis[3])
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	copy_int_arr(cy_rgb, new_cylinder->cy_rgb, 3);
	new_cylinder->cy_height = cy_height;
	new_cylinder->cy_diameter = cy_diameter;
	new_cylinder->cy_coords = vec_4_init_from_coordinates(cy_coords);
	new_cylinder->cy_vec_axis = vec_4_init_from_coordinates(cy_vec_axis);
	new_cylinder->next = NULL;
	return (new_cylinder);
}

void	scene_ambient_add_back(t_ambient **list_ambient, t_ambient *new_ambient)
{
	t_ambient *curr_node;

	if (!new_ambient)
		return ;
	if (!*list_ambient)
	{
		*list_ambient = new_ambient;
		return ;
	}
	curr_node = *list_ambient;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_ambient;
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
void	scene_sphere_add_back(t_sphere **list_sphere, t_sphere *new_sphere)
{
	t_sphere *curr_node;

	if (!new_sphere)
		return ;
	if (!*list_sphere)
	{
		*list_sphere = new_sphere;
		return ;
	}
	curr_node = *list_sphere;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_sphere;
}

void	scene_plane_add_back(t_plane **list_plane, t_plane *new_plane)
{
	t_plane *curr_node;

	if (!new_plane)
		return ;
	if (!*list_plane)
	{
		*list_plane = new_plane;
		return ;
	}
	curr_node = *list_plane;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_plane;
}

void	scene_cylinder_add_back(t_cylinder **list_cylinder, t_cylinder *new_cylinder)
{
	t_cylinder *curr_node;

	if (!new_cylinder)
		return ;
	if (!*list_cylinder)
	{
		*list_cylinder = new_cylinder;
		return ;
	}
	curr_node = *list_cylinder;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;
	curr_node->next = new_cylinder;
}

void	scene_free_ambient_list(t_ambient *ambient_list_head)
{
	t_ambient	*temp;
	t_ambient	*curr;

	curr = ambient_list_head;
	while (curr)
	{
		temp = curr->next;
		free(curr->a_rgb);
		free(curr);
		curr = temp;
	}
}

void	scene_free_camera_list(t_camera *camera_list_head)
{
	t_camera	*temp;
	t_camera	*curr;

	curr = camera_list_head;
	while (curr)
	{
		temp = curr->next;
		vec4_free(&curr->cam_coords);
		vec4_free(&curr->cam_vec_orient);
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
		vec4_free(&curr->l_coords);
		free(curr->l_rgb);
		free(curr);
		curr = temp;
	}
}

void	scene_free_sphere_list(t_sphere *sphere_list_head)
{
	t_sphere	*temp;
	t_sphere	*curr;

	curr = sphere_list_head;
	while (curr)
	{
		temp = curr->next;
		vec4_free(&curr->sp_coords);
		free(curr->sp_rgb);
		free(curr);
		curr = temp;
	}
}

void	scene_free_plane_list(t_plane *plane_list_head)
{
	t_plane	*temp;
	t_plane	*curr;

	curr = plane_list_head;
	while (curr)
	{
		temp = curr->next;
		vec4_free(&curr->pl_coords);
		vec4_free(&curr->pl_vec_normal);
		free(curr->pl_rgb);
		free(curr);
		curr = temp;
	}
}

void	scene_free_cylinder_list(t_cylinder *cylinder_list_head)
{
	t_cylinder	*temp;
	t_cylinder	*curr;

	curr = cylinder_list_head;
	while (curr)
	{
		temp = curr->next;
		vec4_free(&curr->cy_coords);
		vec4_free(&curr->cy_vec_axis);
		free(curr->cy_rgb);
		free(curr);
		curr = temp;
	}
}

void	scene_free_objects(t_scene *scene)
{
	if (scene->sc_ambients)
		scene_free_ambient_list(scene->sc_ambients);
	if (scene->sc_cameras)
		scene_free_camera_list(scene->sc_cameras);
	if (scene->sc_lights)
		scene_free_light_list(scene->sc_lights);
	if (scene->sc_spheres)
		scene_free_sphere_list(scene->sc_spheres);
	if (scene->sc_planes)
		scene_free_plane_list(scene->sc_planes);
	if (scene->sc_cylinders)
		scene_free_cylinder_list(scene->sc_cylinders);
}

t_scene	*scene_init(void)
{
	t_scene	*new_scene;

	new_scene = (t_scene *) malloc(sizeof(t_scene));
	new_scene->sc_ambients = NULL;
	new_scene->sc_cameras = NULL;
	new_scene->sc_lights = NULL;
	new_scene->sc_spheres = NULL;
	new_scene->sc_planes = NULL;
	new_scene->sc_cylinders = NULL;
	return (new_scene);
}

// Debug

void	scene_print_ambient_stats(t_ambient *ambient)
{
	printf("a_ratio = %f\n", ambient->a_ratio);
	printf("a_rgb = %d,%d,%d\n", ambient->a_rgb[0], ambient->a_rgb[1], ambient->a_rgb[2]);
}

void	scene_print_camera_stats(t_camera *camera)
{
	printf("cam_coords = ");
	vec4_print(camera->cam_coords);
	printf("cam_vec_orient = ");
	vec4_print(camera->cam_vec_orient);
	printf("cam_fov = %d\n", camera->cam_fov);
}

void	scene_print_light_stats(t_light *light)
{
	printf("l_coords = ");
	vec4_print(light->l_coords);
	printf("l_brightness = %f\n", light->l_brightness);
	printf("l_rgb = %d,%d,%d\n", light->l_rgb[0], light->l_rgb[1], light->l_rgb[2]);
}
void	scene_print_sphere_stats(t_sphere *sphere)
{
	printf("sp_coords = ");
	vec4_print(sphere->sp_coords);
	printf("sp_diameter = %f\n", sphere->sp_diameter);
	printf("sp_rgb = %d,%d,%d\n", sphere->sp_rgb[0], sphere->sp_rgb[1], sphere->sp_rgb[2]);
}

void	scene_print_plane_stats(t_plane *plane)
{
	printf("pl_coords = ");
	vec4_print(plane->pl_coords);
	printf("pl_vec_normal = ");
	vec4_print(plane->pl_vec_normal);
	printf("pl_rgb = %d,%d,%d\n", plane->pl_rgb[0], plane->pl_rgb[1], plane->pl_rgb[2]);
}

void	scene_print_cylinder_stats(t_cylinder *cylinder)
{
	printf("cy_coords = ");
	vec4_print(cylinder->cy_coords);
	printf("cy_vec_axis = ");
	vec4_print(cylinder->cy_vec_axis);
	printf("cy_diameter = %f\n", cylinder->cy_diameter);
	printf("cy_height = %f\n", cylinder->cy_height);
	printf("cy_rgb = %d,%d,%d\n", cylinder->cy_rgb[0], cylinder->cy_rgb[1], cylinder->cy_rgb[2]);
}

void	scene_print_stats(t_scene *scene)
{
	t_ambient *curr_ambient;
	t_camera *curr_camera;
	t_light *curr_light;
	t_sphere *curr_sphere;
	t_plane *curr_plane;
	t_cylinder *curr_cylinder;

	curr_ambient = scene->sc_ambients;
	curr_camera = scene->sc_cameras;
	curr_light = scene->sc_lights;
	curr_sphere = scene->sc_spheres;
	curr_plane = scene->sc_planes;
	curr_cylinder = scene->sc_cylinders;
	printf("--ambients--\n");
	while (curr_ambient != NULL)
	{
		scene_print_ambient_stats(curr_ambient);
		curr_ambient = curr_ambient->next;
		printf("next\n");
	}
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
	printf("--spheres--\n");
	while (curr_sphere != NULL)
	{
		scene_print_sphere_stats(curr_sphere);
		curr_sphere = curr_sphere->next;
		printf("next\n");
	}
	printf("--planes--\n");
	while (curr_plane != NULL)
	{
		scene_print_plane_stats(curr_plane);
		curr_plane = curr_plane->next;
		printf("next\n");
	}
	printf("--cylinders--\n");
	while (curr_cylinder != NULL)
	{
		scene_print_cylinder_stats(curr_cylinder);
		curr_cylinder = curr_cylinder->next;
		printf("next\n");
	}
}

