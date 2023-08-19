#include "../headers/minirt.h"

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
	if (cylinder->cy_bottom)
	{
		printf("cy_bottom_center_point = ");
		vec3_print(cylinder->cy_bottom);
	}

}

void	scene_print_cone_stats(t_cone *cone)
{
	printf("cn_vec_axis = ");
	vec3_print(cone->cn_vec_axis);
	printf("cn_diameter = %f\n", cone->cn_diameter);
	printf("cn_height = %f\n", cone->cn_height);
	if (cone->cn_bottom)
	{
		printf("cn_bottom_center_point = ");
		vec3_print(cone->cn_bottom);
	}
}

void	scene_print_object_stats(t_object *obj)
{
	printf("obj_coord =");
	vec3_print(obj->ob_coords);
	printf("obj_rgb =");
	vec3_print(obj->ob_rgb);
	printf("obj_specular = %f\n", obj->ob_spec);
	printf("obj_texture_filename = %s\n", obj->has_texture);
	printf("obj_type = %d\n", obj->ob_type);
	if (obj->ob_cylinders)
		scene_print_cylinder_stats(obj->ob_cylinders);
	if (obj->ob_planes)
		scene_print_plane_stats(obj->ob_planes);
	if (obj->ob_spheres)
		scene_print_sphere_stats(obj->ob_spheres);
	if (obj->ob_cones)
		scene_print_cone_stats(obj->ob_cones);
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