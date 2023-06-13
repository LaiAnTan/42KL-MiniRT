#include "minirt.h"

// wOw actually ray-tracing!1!!11!11!!
void	get_image(t_img_info *img_info, void *mlx)
{
	img_info->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_info->addr = mlx_get_data_addr(img_info->img, &img_info->bits_per_pixel, 
		&img_info->line_length, &img_info->endian);
}

void	clean_loop(t_mlx_info *mlx)
{
	if (mlx->img.img != NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->img.img);
		mlx->img.img = NULL;
	}
}

void	write_pixel(t_img_info *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(t_vector *light)
{
	int	r;
	int	g;
	int	b;

	r = light->raw_matrix->stuff[0][0];
	g = light->raw_matrix->stuff[1][0];
	b = light->raw_matrix->stuff[2][0];
	// overflow checker
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;

	// printf("r = %d, g = %d, b = %d\n", r, g, b);

	// my brother in christ, what is transparancy
	return (0 << 24 | r << 16 | g << 8 | b);
}

// runs under the assumtion that the orientation is (0, 0, 1)
matrix_type	get_plane_intersect(matrix_type *point, matrix_type *normal)
{
	matrix_type	val;

	val = (-1 * ((normal[0] * point[0]) + (normal[1] * point[1]))) / normal[2];
	free(normal);
	return (val);
}

double	intersect_plane(t_ray *ray, t_objects *o)
{
	t_vector	*modified_ray_pos;
	t_vector	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, o->position);
	zeroed_pos = v_difference(o->position, o->position);

	// ipad notes... again
	// a = -k(b)
	double	values[2];
	double	k;

	values[0] = v_dotproduct(modified_ray_pos, o->plane->normal_vect);
	values[1] = v_dotproduct(ray->dir_vector, o->plane->normal_vect);

	k = -(values[0] / values[1]);
	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);
	if (k < 0)
		return (ERROR);

	t_vector	*store[2];
	double		mag;

	store[0] = v_scalar_multi(ray->dir_vector, k);
	store[1] = dup_vct(ray->pos_vector);

	free_vector(&ray->pos_vector);
	ray->pos_vector = v_addition(store[1], store[0]);

	free_vector(&store[0]);
	store[0] = v_difference(ray->pos_vector, store[1]); 

	mag = v_magnitude_sqrd(store[0]);
	free_vector(&store[0]);
	free_vector(&store[1]);
	return (mag);
}

void solve_quad(double	*coefficients, double *result)
{
	double	a;
	double	b;
	double	c;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];

	// walao make a bzero nia
	for (int i = 0; i < 3; ++i)
		result[i] = 0;

	result[0] = (b * b) - ( 4 * a * c );
	// determinant is less than zero
	if (result[0] < 0)
		return ;
	result[1] = ((-1 * b) + sqrt(result[0])) / (2 * a);
	result[2] = ((-1 * b) - sqrt(result[0])) / (2 * a);
}

// ax^2 + bx + c
double	intersect_circle(t_ray	*ray, t_objects *o)
{
	double	values[3];
	double	coefficients[3];
	double	mag;

	// set coefficients also based on the notes on your ipad

	// me cheese this (not sure if works :skull)
	t_vector	*modified_ray_pos;
	t_vector	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, o->position);
	zeroed_pos = v_difference(o->position, o->position);
	// in theory this would work (theory)

	// le ipad formulas
	coefficients[0] = v_magnitude_sqrd(ray->dir_vector);
	coefficients[1] = v_dotproduct(modified_ray_pos, ray->dir_vector) * 2;
	coefficients[2] = v_magnitude_sqrd(modified_ray_pos) - (o->circle->radius * o->circle->radius);

	solve_quad(coefficients, values);
	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);

	if (values[0] < 0)
		return (ERROR);
	if (values[1] < 0 && values[2] < 0)
		return (ERROR);

	// // debug msg
	// printf("Ori Vector = ");
	// print_vector(ray->pos_vector);
	// printf("solutions = %.2f, %.2f\n", values[1], values[2]);

	values[0] = fmin(values[1], values[2]);
	if (values[0] < 0)
		values[0] = fmax(values[1], values[2]);
	
	// debug msg
	// printf("k = %.2f\n", values[0]);
	t_vector	*store[2];

	store[0] = v_scalar_multi(ray->dir_vector, values[0]);
	store[1] = dup_vct(ray->pos_vector);

	// // debug msg
	// printf("Direction Vector = ");
	// print_vector(ray->dir_vector);
	// printf("Scaled Vector = ");
	// print_vector(store[0]);

	free_vector(&ray->pos_vector);
	ray->pos_vector = v_addition(store[1], store[0]);

	// // debug msg
	// printf("New Vector = ");
	// print_vector(ray->pos_vector);
	// printf("\n");

	free_vector(&store[0]);
	store[0] = v_difference(ray->pos_vector, store[1]); 
	mag = v_magnitude_sqrd(store[0]);

	free_vector(&store[0]);
	free_vector(&store[1]);
	return (mag);
}

double	absolute(double val)
{
	if (val < 0)
		return (-1 * val);
	else
		return (val);
}

double	to_radian(double degree)
{
	return (degree * M_PI / 180);
}

double	to_degree(double rad)
{
	return (rad * 180 / M_PI);
}

// void	calculate_ray_positions(double *store, int x, int y)
// {
// 	// othrogonathic bla bla yeah this sucks
// 	store[0] = x - (WIDTH / 2);
// 	store[1] = (HEIGHT / 2) - y;
// 	store[2] = 0;
// }

// // projects a ray
// t_ray	*project_ray(int x, int y, t_cam *camera)
// {
// 	double		*store;
// 	t_vector	*pos_vector;

// 	store = get_val(camera->position);
// 	calculate_ray_positions(store, x, y);
// 	pos_vector = init_vector_intarr(store);
// 	free(store);
// 	return (init_ray(pos_vector, dup_vct(camera->orientation)));
// }

void	calculate_ray_positions(double *store, double x, double y)
{
	double	height = HEIGHT;
	double	width = WIDTH;

	double	hori_fov = to_radian(HORI_FOV);
	double	verti_fov = 2 * atan((height / width) * tan(hori_fov / 2));
	// printf("FOV (%.2f, %.2f)\n", to_degree(hori_fov), to_degree(verti_fov));

	double	hori_fov_per_x = hori_fov / width;
	double	verti_fov_per_y = verti_fov / height;

	double	x_relative_to_mid  = x - (width / 2);
	double	y_relative_to_mid = (height / 2) - y;
	// printf("relative = (%.2f, %.2f)\n", x_relative_to_mid, y_relative_to_mid);

	double	hori_angle = absolute(x_relative_to_mid) * hori_fov_per_x;
	double	verti_angle = absolute(y_relative_to_mid) * verti_fov_per_y;
	// printf("Angles (%.2f, %.2f)\n", to_degree(hori_angle), to_degree(verti_angle));

	double	alpha = (width / 2) / (tan(hori_fov / 2));
	// printf("that one constant line = %.2f\n", alpha); 

	double	acc_x = alpha * tan(hori_angle);

	if (x_relative_to_mid < 0)
		acc_x *= -1;

	double	acc_y = alpha * tan(verti_angle);
	if (y_relative_to_mid < 0)
		acc_y *= -1;

	// printf("x and y (%.2f, %.2f)\n", acc_x, acc_y);

	// hang on.
	double	acc_z = alpha;

	store[0] = acc_x;
	store[1] = acc_y; 
	store[2] = acc_z;
}

// projects a ray
t_ray	*project_ray(double x, double y, t_cam *camera)
{
	double		*store;
	t_vector	*store_vec;
	t_vector	*dir_vector;

	store = get_val(camera->position);

	calculate_ray_positions(store, x, y);
	store_vec = init_vector_intarr(store);
	dir_vector = v_get_unit_v(store_vec);
	free_vector(&store_vec);
	free(store);

	return (init_ray(dup_vct(camera->position), dir_vector));
}

t_objects	*get_closest_object(t_ray *ray, t_scene *scene, int closest)
{
	t_objects	*cur;
	t_objects	*closest_object_src;
	double		closest_object;
	double		r_to_o;
	t_ray		*collide_obj;
	t_ray		*closest_ray;

	cur = scene->objs;
	closest_object = INFINITY;
	closest_object_src = NULL;
	closest_ray = NULL;
	while (cur)
	{
		// this is seriously slow
		// will optimize this later (maybe just return k value)
		collide_obj = dup_ray(ray);

		if (cur->type == CIRCLE)
			r_to_o = intersect_circle(collide_obj, cur);
		else if (cur->type == PLANE)
			r_to_o = intersect_plane(collide_obj, cur);

		// means collided d
		if (r_to_o != ERROR)
		{
			if (!closest)
			{
				free_ray(&collide_obj);
				return (cur);
			}
			if (r_to_o < closest_object)
			{
				closest_object = r_to_o;
				closest_object_src = cur;
				if (closest_ray)
					free_ray(&closest_ray);
				closest_ray = dup_ray(collide_obj);
			}
		}
		free_ray(&collide_obj);
		cur = cur->next;
	}
	if (closest_object_src)
	{
		free_vector(&ray->pos_vector);
		ray->pos_vector = dup_vct(closest_ray->pos_vector);
	}
	if (closest_ray)
		free_ray(&closest_ray);
	return (closest_object_src);
}

double	calculate_d_from_l(t_ray *r, t_light *l, t_scene *scene)
{
	t_vector	*r_to_l;
	t_ray		*to_light;
	t_objects	*collided_obj;

	r_to_l = v_difference(l->position, r->pos_vector);

	to_light = dup_ray(r);
	free_vector(&to_light->dir_vector);
	to_light->dir_vector = v_get_unit_v(r_to_l);
	free_vector(&to_light->pos_vector);
	to_light->pos_vector = v_addition(r->pos_vector, to_light->dir_vector);

	collided_obj = get_closest_object(to_light, scene, 0);
	free_vector(&r_to_l);
	free_ray(&to_light);

	if (collided_obj == NULL)
		return (SUCCESS);
	return (ERROR);
}

void	ambient_color(t_ray	*ray, t_ambient *a, t_objects *o)
{
	double		amb_coefficient = AMBIENCE_FACTOR;
	t_vector	*store[2];
	t_vector	*new;

	free_vector(&ray->a_color);
	if (!o)
	{
		ray->a_color = v_scalar_multi(a->color, amb_coefficient);
	}
	else
	{
		store[0] = v_scalar_multi(a->color, amb_coefficient);
		store[1] = v_scalar_multi(o->color, amb_coefficient);
		ray->a_color = v_addition(store[0], store[1]);
		free_vector(&store[0]);
		free_vector(&store[1]);
	}
}

t_vector	*inverse_color(t_vector	*c)
{
	int		i;
	matrix_type	i_rgb[3];
	matrix_type	*c_stuff;

	c_stuff = get_val(c);
	i = 0;
	while (i < 3)
	{
		i_rgb[i] = absolute(255 - c_stuff[i]);
		++i;
	}
	free(c_stuff);
	return (init_vector_intarr(i_rgb));
}

void	remove_negative(t_vector *v)
{
	int	i;

	i = 0; 
	while (i < 3)
	{
		if (v->raw_matrix->stuff[i][0] < 0)
			v->raw_matrix->stuff[i][0] = 0;
		++i;
	}
}

void	calculate_diffuse_color(t_ray *r, t_light *l, t_objects *o, double costheta)
{
	double	angles = acos(costheta);
	double	diff_strength = DIFFUSE_FACTOR;

	t_vector	*d_c; // object diffuse color
	t_vector	*a_o_c; // absorbed object color
	t_vector	*store[2];

	a_o_c = inverse_color(o->color);
	store[0] = v_difference(l->color, a_o_c);
	remove_negative(store[0]);

	d_c = v_scalar_multi(store[0], (costheta * diff_strength));
	store[1] = v_addition(r->d_color, d_c);

	free_vector(&d_c);
	free_vector(&a_o_c);
	free_vector(&store[0]);
	free_vector(&r->d_color);
	r->d_color = store[1];
}

void	diffuse_the_bomb(t_ray *r, t_light *l, t_objects *o)
{
	t_vector	*a;
	t_vector	*a_norm;
	t_vector	*b;
	t_vector	*b_norm;

	a = v_difference(l->position, r->pos_vector);
	a_norm = v_get_unit_v(a);

	// get normal to intersection
	if (o->type == CIRCLE)
		b = v_difference(r->pos_vector, o->position);
	else if (o->type == PLANE)
		b = dup_vct(o->plane->normal_vect);

	b_norm = v_get_unit_v(b);

	double	costheta;
	costheta = absolute(v_dotproduct(a_norm, b_norm));
	// printf("angle collided = %.2f\n", (acos(costheta) * 180 / M_PI));

	free_vector(&a);
	free_vector(&a_norm);
	free_vector(&b);
	free_vector(&b_norm);
	calculate_diffuse_color(r, l, o, costheta);
}

void	calculate_result_color(t_ray *r)
{
	t_vector	*store[2];

	// printf("ambience = ");
	// print_vector(r->a_color);
	// printf("diffuse color = ");
	// print_vector(r->d_color);

	store[0] = v_addition(r->a_color, r->d_color);
	free_vector(&r->color);
	r->color = store[0];

	// printf("Color = ");
	// print_vector(r->color);
	// printf("\n");
}

void	shadow_diffuse(t_ray *ray)
{
	matrix_type	shadow[3] = {0,0,0};
	// hard shadow
	free_vector(&ray->d_color);
	ray->d_color = init_vector_intarr(shadow);
}

void	do_ray_stuff(double x, double y, t_scene *scene, t_mlx_info *mlx)
{
	t_light		*light;
	t_objects	*closest_object_src;
	t_ray		*ray;

	// printf("[%d,%d]\n",x,y);
	ray = project_ray(x, y, scene->camera);
	// print_vector(ray->pos_vector);
	// print_vector(ray->dir_vector);
	// printf("\n");

 //  detect collision
 //  ----------------------------------------------------------------------------

	closest_object_src = get_closest_object(ray, scene, 1);
	if (closest_object_src)
		ray->type = COLLIDED;
	// printf("ray->type = %d\n", ray->type);

 //  detect light source
 //  ----------------------------------------------------------------------------

	double		p_from_light;

	if (ray->type == COLLIDED)
	{
		ray->type = SHADOW;
		light = scene->lights;
		while (light)
		{
			p_from_light = calculate_d_from_l(ray, light, scene);
			if (p_from_light == ERROR)
			{
				if (!light->next && ray->type == SHADOW)
				{
					// is a shadow ray
					ray->type = SHADOW;
					shadow_diffuse(ray);
				}
				light = light->next;
				continue;
			}
			else
			{
				// calculate diffuse lighting
				ray->type = COLLIDED;
				diffuse_the_bomb(ray, light, closest_object_src);
			}
			light = light->next;
		}
	}

//  -----------------------------------------------------------------------------

	// ambient
	ambient_color(ray, scene->ambient, closest_object_src);

//  -----------------------------------------------------------------------------
	
	calculate_result_color(ray);
	write_pixel(&mlx->img, x, y, create_trgb(ray->color));
	free_ray(&ray);

	// printf("\n");
}

void	kewl_quirky_raytrace(t_scene *scene, t_mlx_info *mlx)
{
	double	x;
	double	y;
	double	rays_per_x = WIDTH / RAYS_IN_X;
	double	rays_per_y = HEIGHT / RAYS_IN_Y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			do_ray_stuff(x, y, scene, mlx);
			x += rays_per_x;
		}
		y += rays_per_y;
	}
}

void	free_scene(t_scene	*scene)
{
	free_cam(&scene->camera);
	free_objects(&scene->objs);
	free_light(&scene->lights);
	free_ambient(&scene->ambient);
}

void	free_mlx(t_mlx_info *mlx)
{
	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx, mlx->img.img);
	if (mlx->mlx_win)
	{
		mlx_clear_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	}
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

// int main()
// {
// 	t_scene		scene;
// 	t_mlx_info	mlx;
// 	int			loop;


// 	mlx.mlx = mlx_init();
// 	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
// 	mlx.img.img = NULL;
// 	loop = 0;
// 	while (1)
// 	{
// 		printf("loop = %d\n", loop);
// 		set_the_scene(&scene, loop);
// 		get_image(&mlx.img, mlx.mlx);
// 		kewl_quirky_raytrace(&scene, &mlx);
// 		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
// 		clean_loop(&mlx);
// 		free_scene(&scene);
// 		loop += 2;
// 		if (loop > HEIGHT)
// 			loop = -1 * HEIGHT;
// 	}
// 	mlx_loop(mlx.mlx);
// }

// // single loop
// # include <unistd.h>
// int main()
// {
// 	t_scene		scene;
// 	t_mlx_info	mlx;
// 	int			loop;


// 	mlx.mlx = mlx_init();
// 	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
// 	mlx.img.img = NULL;
// 	loop = 0;
// 	set_the_scene(&scene, loop);

// 	get_image(&mlx.img, mlx.mlx);
// 	kewl_quirky_raytrace(&scene, &mlx);
// 	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
// 	clean_loop(&mlx);

// 	sleep(2);
// 	free_scene(&scene);
// 	free_mlx(&mlx);
// }

// two loop
# include <unistd.h>
int main()
{
	t_scene		scene;
	t_mlx_info	mlx;
	int			loop;


	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
	mlx.img.img = NULL;
	loop = 0;
	set_the_scene(&scene, loop);

	int i = 2;
	while (i)
	{
		get_image(&mlx.img, mlx.mlx);
		kewl_quirky_raytrace(&scene, &mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
		clean_loop(&mlx);
		--i;
	}
	sleep(2);
	free_scene(&scene);
	free_mlx(&mlx);
}