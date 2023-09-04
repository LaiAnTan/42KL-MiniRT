/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:37 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/04 23:29:24 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

/*
heads up, right hand orienation (0,0,-1)
if left hand orientation (0,0,1),
double	x_relative_to_mid = (WIDTH / 2) - x;
double	y_relative_to_mid = (HEIGHT / 2) - y
double	alpha = (WIDTH / 2) / (tan(hori_fov / 2));

store[0] = acc_x
store[1] = acc_y
store[z] = acc_z

original function:

double	hori_fov = to_radian(fov);
double	verti_fov = 2 * atan((HEIGHT / WIDTH) * tan(hori_fov / 2));
double	hori_fov_per_x = hori_fov / WIDTH;
double	verti_fov_per_y = verti_fov / HEIGHT;
double	x_relative_to_mid = (WIDTH / 2) - x;
double	y_relative_to_mid = y - (HEIGHT / 2);
double	hori_angle = abs_double(x_relative_to_mid) * hori_fov_per_x;
double	verti_angle = abs_double(y_relative_to_mid) * verti_fov_per_y;
double	alpha = - (WIDTH / 2) / (tan(hori_fov / 2));
store[0] = alpha * tan(hori_angle);
store[1] = alpha * tan(verti_angle);
store[2] = alpha;
if (x_relative_to_mid < 0)
	store[0] *= -1;
if (y_relative_to_mid < 0)
	store[1] *= -1;

*/
void	calculate_ray_positions(double store[3], double x, double y, double fov)
{
	double	verti_fov;
	double	hori_angle;
	double	verti_angle;
	double	alpha;

	verti_fov = 2 * atan((HEIGHT / WIDTH) * tan(to_radian(fov) / 2));
	hori_angle = abs_double((WIDTH / 2) - x) * (to_radian(fov) / WIDTH);
	verti_angle = abs_double(y - (HEIGHT / 2)) * (verti_fov / HEIGHT);
	alpha = - (WIDTH / 2) / (tan(to_radian(fov) / 2));
	store[0] = alpha * tan(hori_angle);
	store[1] = alpha * tan(verti_angle);
	store[2] = alpha;
	if ((WIDTH / 2) - x < 0)
		store[0] *= -1;
	if (y - (HEIGHT / 2) < 0)
		store[1] *= -1;
}

// projects a ray
t_ray	*project_ray(double x, double y, t_camera *camera)
{
	double	store[3];
	t_vec3	*dir_vector;

	calculate_ray_positions(store, x, y, camera->cam_fov);
	dir_vector = vec3_normalize(vec3_init_from_array(store), O_REPLACE);
	return (init_ray(vec3_dup(camera->cam_coords), dir_vector));
}

/*
steps:
1. project ray
2. detect collision (intersection)
	if collided, find light source
		if has light source, calc diffuse and specular color
4. calculate ambient color
5. result color = diffuse + specular + ambient
5. set color of pixel
*/
void	do_ray_stuff(double x, double y, t_data *data)
{
	double		k_val;
	double		p_from_light;
	t_ray		*ray;
	t_light		*light;
	t_object	*closest_object_src;

	ray = project_ray(x, y, data->scene->sc_cameras);
	closest_object_src = get_closest_object(ray, data->scene->sc_objs, 1,
			&k_val);
	if (closest_object_src)
	{
		move_ray(ray, k_val);
		ray->type = COLLIDED;
	}
	if (ray->type == COLLIDED)
	{
		ray->type = SHADOW;
		light = data->scene->sc_lights;
		while (light)
		{
			p_from_light = get_closest_light_runner(ray, light,
					data->scene->sc_objs);
			if (p_from_light != ERROR)
				diffuse_the_bomb(ray, light, closest_object_src);
			light = light->next;
		}
	}
	if (data->scene->sc_ambients)
		ambient_color(ray, data->scene->sc_ambients, closest_object_src);
	calculate_result_color(ray);
	write_pixel(data->mlx->render_img, x, y, create_trgb(ray->color));
	free_ray(&ray);
}

void	switch_image(t_data *image)
{
	t_img_info	*temp;

	temp = image->mlx->cur_img;
	image->mlx->cur_img = image->mlx->render_img;
	image->mlx->render_img = temp;
}

void	raytrace(t_data *data)
{
	double	x;
	double	y;
	double	rays_per_x;
	double	rays_per_y;

	rays_per_x = WIDTH / RAYS_IN_X;
	rays_per_y = HEIGHT / RAYS_IN_Y;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			do_ray_stuff(x, y, data);
			x += rays_per_x;
		}
		y += rays_per_y;
	}
	switch_image(data);
}
