#include "../headers/minirt.h"

t_ambient	*scene_new_ambient(int a_rgb[3], float a_ratio)
{
	t_ambient	*new_ambient;

	new_ambient = (t_ambient *) malloc(sizeof(t_ambient));
	copy_int_arr(a_rgb, new_ambient->a_rgb, 3);
	new_ambient->a_ratio = a_ratio;
	new_ambient->next = NULL;
	return (new_ambient);
}

t_camera	*scene_new_camera(int cam_fov, float cam_coords[3], float cam_vec_orient[3])
{
	t_camera	*new_camera;

	new_camera = (t_camera *) malloc(sizeof(t_camera));
	new_camera->cam_fov = cam_fov;
	copy_float_arr(cam_coords, new_camera->cam_coords, 3);
	copy_float_arr(cam_vec_orient, new_camera->cam_vec_orient, 3);
	new_camera->next = NULL;
	return (new_camera);
}

t_light		*scene_new_light(int l_rgb[3], float l_coords[3], float l_brightness)
{
	t_light		*new_light;

	new_light = (t_light *) malloc(sizeof(t_light));
	copy_int_arr(l_rgb, new_light->l_rgb, 3);
	copy_float_arr(l_coords, new_light->l_coords, 3);
	new_light->l_brightness = l_brightness;
	new_light->next = NULL;
	return (new_light);
}

t_sphere	*scene_new_sphere(int sp_rgb[3], float sp_diameter, float sp_coords[3])
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *) malloc(sizeof(t_sphere));
	copy_int_arr(sp_rgb, new_sphere->sp_rgb, 3);
	new_sphere->sp_diameter = sp_diameter;
	copy_float_arr(sp_coords, new_sphere->sp_coords, 3);
	new_sphere->next = NULL;
	return (new_sphere);
}

t_plane		*scene_new_plane(int pl_rgb[3], float pl_coords[3], float pl_vec_normal[3])
{
	t_plane		*new_plane;

	new_plane = (t_plane *) malloc(sizeof(t_plane));
	copy_int_arr(pl_rgb, new_plane->pl_rgb, 3);
	copy_float_arr(pl_coords, new_plane->pl_coords, 3);
	copy_float_arr(pl_vec_normal, new_plane->pl_vec_normal, 3);
	new_plane->next = NULL;
	return (new_plane);
}

t_cylinder	*scene_new_cylinder(int cy_rgb[3], float cy_height, float cy_diameter, float cy_coords[3], float cy_vec_axis[3])
{
	t_cylinder	*new_cylinder;

	new_cylinder = (t_cylinder *) malloc(sizeof(t_cylinder));
	copy_int_arr(cy_rgb, new_cylinder->cy_rgb, 3);
	new_cylinder->cy_height = cy_height;
	new_cylinder->cy_diameter = cy_diameter;
	copy_float_arr(cy_coords, new_cylinder->cy_coords, 3);
	copy_float_arr(cy_vec_axis, new_cylinder->cy_vec_axis, 3);
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
	t_ambient *curr_node;

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
	t_ambient *curr_node;

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
	t_ambient *curr_node;

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
	t_ambient *curr_node;

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
	t_ambient *curr_node;

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