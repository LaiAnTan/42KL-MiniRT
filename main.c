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
int	intersect_circle(t_ray	*ray, t_circle *circle)
{
	double	values[3];
	double	coefficients[3];
	double	mag;

	// set coefficients also based on the notes on your ipad

	// me cheese this (not sure if works :skull)
	t_vector	*modified_ray_pos;
	t_vector	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, circle->position);
	zeroed_pos = v_difference(circle->position, circle->position);
	// in theory this would work (theory)

	// le ipad formulas
	coefficients[0] = v_magnitude_sqrd(ray->dir_vector);
	coefficients[1] = v_dotproduct(modified_ray_pos, ray->dir_vector) * 2;
	coefficients[2] = v_magnitude_sqrd(modified_ray_pos) - (circle->radius * circle->radius);

	solve_quad(coefficients, values);
	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);

	if (values[0] < 0)
		return (ERROR);

	t_vector	*store[2];

	if (values[1] < 0 && values[2] < 0)
		return (ERROR);

	// // debug msg
	// printf("Vector = ");
	// print_vector(ray->pos_vector);
	// printf("solutions = %.2f, %.2f\n", values[1], values[2]);

	values[0] = fmin(values[1], values[2]);
	if (values[0] < 0)
		values[0] = fmax(values[1], values[2]);
	
	// debug msg
	// printf("k = %.2f\n", values[0]);

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

void	calculate_ray_positions(double *store, int x, int y)
{
	store[0] = x - (WIDTH / 2);
	store[1] = (HEIGHT / 2) - y;
	store[2] = 0;
}

// projects a ray
t_ray	*project_ray(int x, int y, t_cam *camera)
{
	double		*store;
	t_vector	*pos_vector;

	store = get_val(camera->position);
	calculate_ray_positions(store, x, y);
	pos_vector = init_vector_intarr(store);
	free(store);
	return (init_ray(pos_vector, dup_vct(camera->orientation)));
}

double	calculate_d_from_l(t_ray *r, t_light *l, t_scene *scene)
{
	t_vector	*r_to_l;
	t_ray		*to_light;
	t_circle	*cur;

	// // debug msg
	// printf("Calculating Light ---\n\n");

	r_to_l = v_difference(l->position, r->pos_vector);

	cur = scene->circles;
	while (cur)
	{
		to_light = dup_ray(r);
		free_vector(&to_light->dir_vector);
		to_light->dir_vector = v_normalize(r_to_l);
		free_vector(&to_light->pos_vector);
		to_light->pos_vector = v_addition(r->pos_vector, to_light->dir_vector);
		if (intersect_circle(to_light, cur) == SUCCESS)
		{
			free_vector(&r_to_l);
			free_ray(&to_light);
			return (ERROR);
		}
		free_ray(&to_light);
		cur = cur->next;
	}
	free_vector(&r_to_l);
	return (SUCCESS);
}

void	ambient_color(t_ray	*ray, t_ambient *a)
{
	t_vector	*new;

	new = init_vector(m_multiplication(a->multiply_mtrx, ray->color->raw_matrix));
	free_vector(&ray->color);
	ray->color = new;
	// printf("Color is now = \n");
	// print_vector(ray->color);
	// printf("\n");
}

void	object_collide_color(t_ray *r, t_circle *c)
{
	if (c)
	{
		free_vector(&r->color);
		r->color = dup_vct(c->color);
	}
}

void	diffuse_the_bomb(t_ray *r, t_light *l, t_circle *o)
{
	t_vector	*a;
	t_vector	*a_norm;

	a = v_difference(l->position, r->pos_vector);
	print_vector(a);
	a_norm = v_normalize(a);

	t_vector	*b;
	t_vector	*b_norm;

	b = v_difference(r->pos_vector, o->position);
	b_norm = v_normalize(b);
	print_vector(b);

	// dot product
	// a x b = |a||b| cos theta
	// if a and b are both normal vector
	// a x b = cos theta

	double	costheta;
	costheta = v_dotproduct(a_norm, b_norm);

	free_vector(&a);
	free_vector(&a_norm);
	free_vector(&b);
	free_vector(&b_norm);
	printf("cos theta = %.2f\n", costheta);

	double	angles = acos(costheta);
	double	ninety = M_PI / 2;

	printf("Angles = %.2f rad, %.2f degree\n", angles, (angles * 180) / M_PI);
	printf("\n");
}

void	do_ray_stuff(int x, int y, t_scene *scene, t_mlx_info *mlx)
{
	t_light		*light;
	t_circle	*cur;
	t_ray		*ray;

	ray = project_ray(x, y, scene->camera);
	// print_vector(ray->pos_vector);

	double		closest_object;
	t_circle	*closest_object_src;
	double		r_to_c;

 //  detect collision
 //  ----------------------------------------------------------------------------

	cur = scene->circles;
	closest_object = INFINITY;
	closest_object_src = NULL;
	while (cur)
	{
		r_to_c = intersect_circle(ray, cur);
		if (r_to_c != ERROR)
		{
			if (r_to_c < closest_object)
			{
				closest_object = r_to_c;
				closest_object_src = cur;
			}
			ray->type = COLLIDED;
		}
		cur = cur->next;
	}
	object_collide_color(ray, closest_object_src);

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
			if (p_from_light == -1)
			{
				if (!light->next && ray->type == SHADOW)
					ray->type = SHADOW;	
				light = light->next;
				continue;
			}
			else
			{
				// calculate diffuse lighting
				diffuse_the_bomb(ray, light, closest_object_src);
				ray->type = COLLIDED;
			}
			light = light->next;
		}
	}

//  -----------------------------------------------------------------------------

	// ambient
	ambient_color(ray, scene->ambient);

//  -----------------------------------------------------------------------------
	write_pixel(&mlx->img, x, y, create_trgb(ray->color));
	free_ray(&ray);
}

void	kewl_quirky_raytrace(t_scene *scene, t_mlx_info *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			do_ray_stuff(x, y, scene, mlx);
			++x;
		}
		++y;
	}
}

void	free_scene(t_scene	*scene)
{
	free_cam(&scene->camera);
	free_circle(&scene->circles);
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
// 		set_the_scene(&scene, loop);
// 		get_image(&mlx.img, mlx.mlx);
// 		kewl_quirky_raytrace(&scene, &mlx);
// 		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
// 		clean_loop(&mlx);
// 		free_scene(&scene);
// 		loop += 10;
// 		if (loop > HEIGHT)
// 			loop = -1 * HEIGHT;
// 	}
// 	mlx_loop(mlx.mlx);
// }

// single loop
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

	get_image(&mlx.img, mlx.mlx);
	kewl_quirky_raytrace(&scene, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	clean_loop(&mlx);

	sleep(2);
	free_scene(&scene);
	free_mlx(&mlx);
}

// // pure m a t h s
// int main()
// {
// 	t_scene		scene;
// 	t_mlx_info	mlx;
// 	int			loop;

// 	loop = 0;
// 	set_the_scene(&scene);
// 	kewl_quirky_raytrace(&scene, &mlx);
// }