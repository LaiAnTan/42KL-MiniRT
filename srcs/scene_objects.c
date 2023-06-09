#include "../headers/minirt.h"

t_ambient	*scene_new_ambient(int a_rgb[3], double a_ratio)
{
	t_ambient	*new_ambient;

	new_ambient = (t_ambient *) malloc(sizeof(t_ambient));
	copy_int_arr(a_rgb, new_ambient->a_rgb, 3);
	new_ambient->a_ratio = (double) a_ratio;
	new_ambient->next = NULL;
	return (new_ambient);
}

t_camera	*scene_new_camera(int cam_fov, double cam_coords[3], double cam_vec_orient[3])
{
	t_camera	*new_camera;

	new_camera = (t_camera *) malloc(sizeof(t_camera));
	new_camera->cam_fov = cam_fov;
	copy_double_arr(cam_coords, new_camera->cam_coords, 3);
	copy_double_arr(cam_vec_orient, new_camera->cam_vec_orient, 3);
	new_camera->next = NULL;
	return (new_camera);
}

t_light		*scene_new_light(int l_rgb[3], double l_coords[3], double l_brightness)
{
	t_light		*new_light;

	new_light = (t_light *) malloc(sizeof(t_light));
	copy_int_arr(l_rgb, new_light->l_rgb, 3);
	copy_double_arr(l_coords, new_light->l_coords, 3);
	new_light->l_brightness = l_brightness;
	new_light->next = NULL;
	return (new_light);
}

t_sphere	*scene_new_sphere(int sp_rgb[3], double sp_diameter, double sp_coords[3])
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *) malloc(sizeof(t_sphere));
	copy_int_arr(sp_rgb, new_sphere->sp_rgb, 3);
	new_sphere->sp_diameter = sp_diameter;
	copy_double_arr(sp_coords, new_sphere->sp_coords, 3);
	new_sphere->next = NULL;
	return (new_sphere);
}

t_plane		*scene_new_plane(int pl_rgb[3], double pl_coords[3], double pl_vec_normal[3])
{
	t_plane		*new_plane;

	new_plane = (t_plane *) malloc(sizeof(t_plane));
	copy_int_arr(pl_rgb, new_plane->pl_rgb, 3);
	copy_double_arr(pl_coords, new_plane->pl_coords, 3);
	copy_double_arr(pl_vec_normal, new_plane->pl_vec_normal, 3);
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
	copy_double_arr(cy_coords, new_cylinder->cy_coords, 3);
	copy_double_arr(cy_vec_axis, new_cylinder->cy_vec_axis, 3);
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

// Debug

void	scene_print_ambient_stats(t_ambient *ambient)
{
	printf("a_ratio = %f\n", ambient->a_ratio);
	printf("a_rgb = %d,%d,%d\n", ambient->a_rgb[0], ambient->a_rgb[1], ambient->a_rgb[2]);
}

void	scene_print_camera_stats(t_camera *camera)
{
	printf("cam_coords = %f,%f,%f\n", camera->cam_coords[0], camera->cam_coords[1], camera->cam_coords[2]);
	printf("cam_vec_orient = %f,%f,%f\n", camera->cam_vec_orient[0], camera->cam_vec_orient[1], camera->cam_vec_orient[2]);
	printf("cam_fov = %d\n", camera->cam_fov);
}

void	scene_print_light_stats(t_light *light)
{
	printf("l_coords = %f,%f,%f\n", light->l_coords[0], light->l_coords[1], light->l_coords[2]);
	printf("l_brightness = %f\n", light->l_brightness);
	printf("l_rgb = %d,%d,%d\n", light->l_rgb[0], light->l_rgb[1], light->l_rgb[2]);
}
void	scene_print_sphere_stats(t_sphere *sphere)
{
	printf("sp_coords = %f,%f,%f\n", sphere->sp_coords[0],sphere->sp_coords[1], sphere->sp_coords[2]);
	printf("sp_diameter = %f\n", sphere->sp_diameter);
	printf("sp_rgb = %d,%d,%d\n", sphere->sp_rgb[0], sphere->sp_rgb[1], sphere->sp_rgb[2]);
}

void	scene_print_plane_stats(t_plane *plane)
{
	printf("pl_coords = %f,%f,%f\n", plane->pl_coords[0], plane->pl_coords[1], plane->pl_coords[2]);
	printf("pl_vec_normal = %f,%f,%f\n", plane->pl_vec_normal[0], plane->pl_vec_normal[1], plane->pl_vec_normal[2]);
	printf("pl_rgb = %d,%d,%d\n", plane->pl_rgb[0], plane->pl_rgb[1], plane->pl_rgb[2]);
}

void	scene_print_cylinder_stats(t_cylinder *cylinder)
{
	printf("cy_coords = %f,%f,%f\n", cylinder->cy_coords[0], cylinder->cy_coords[1], cylinder->cy_coords[2]);
	printf("cy_vec_axis = %f,%f,%f\n", cylinder->cy_vec_axis[0], cylinder->cy_vec_axis[1], cylinder->cy_vec_axis[2]);
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