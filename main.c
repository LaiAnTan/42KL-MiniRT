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

int	create_trgb(int r, int g, int b)
{
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

	// oh yeah set coefficients also based on the notes on your ipad
	// unfortunately you kinda forgot to take into account that 
	// the circle position changes?
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

	if (values[0] < 0)
	{
		free_vector(&modified_ray_pos);
		free_vector(&zeroed_pos);
		return (FAILURE);
	}

	t_vector	*store[2];

	if (values[1] < 0 && values[2] < 0)
	{
		free_vector(&modified_ray_pos);
		free_vector(&zeroed_pos);
		return (FAILURE);
	}

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

	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);
	free_vector(&store[0]);
	free_vector(&store[1]);

	return (SUCCESS);
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
			// // debug msg
			// printf("This is a shadow Ray\n______________________\n\n");

			free_vector(&r_to_l);
			free_ray(&to_light);
			return (ERROR);
		}
		free_ray(&to_light);
		cur = cur->next;
	}

	// doesnt intersect any circle, calculate distance
	// for what LMAO
	// double		mag;

	// mag = v_magnitude(r_to_l);

	// // debug msg
	// printf("Ray Vector = ");
	// print_vector(r->pos_vector);
	// printf("Light Vector = ");
	// print_vector(l->position);
	// printf("Ray to Light Vector = ");
	// print_vector(r_to_l);
	// free_vector(&r_to_l);


	// deprecated code wowsies
	// double	ret;

	// ret = (l->intensity) / (4 * M_PI * (mag * mag));

	// // debug msg
	// printf("Distance = %f\n", mag);
	// printf("Intensity = %f\n", ret);
	// printf("Ratio = %f\n", (ret / (l->intensity / (4 * M_PI))));
	// printf("\n");

	return (SUCCESS);
}

void	do_ray_stuff(int x, int y, t_scene *scene, t_mlx_info *mlx)
{
	double		largest_p;
	t_light		*light;
	t_circle	*cur;
	t_ray		*ray;
	double		p_from_light;

	ray = project_ray(x, y, scene->camera);
	cur = scene->circles;
	largest_p = 0;

	// print_vector(ray->pos_vector);

	while (cur)
	{
		if (intersect_circle(ray, cur) == SUCCESS)
		{
			ray->type = COLLIDED;
			break;
		}
		cur = cur->next;
	}
	if (ray->type == COLLIDED)
	{
		ray->type = SHADOW;
		light = scene->lights;
	
		p_from_light = 0;

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
				ray->type = COLLIDED;
			}
			if (p_from_light > largest_p)
				largest_p = p_from_light;
			light = light->next;
		}

	}

	if (ray->type == COLLIDED)
	{
		// printf("Collided with circle\n");
		write_pixel(&mlx->img, x, y, create_trgb(255, 0, 0));
	}
	else if (ray->type == SHADOW)
	{
		// printf("Shadow ray\n");
		write_pixel(&mlx->img, x, y, create_trgb(115, 0, 0));
	}
	else
	{
		// printf("Into the unkown\n");
		write_pixel(&mlx->img, x, y, create_trgb(0, 0, 0));
	}

	// printf("\n");

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

// bunch of hard code and DEBUG
void	set_the_scene(t_scene *scene, double x)
{
	(void) x;
	scene->camera = init_cam(0,0,0);
	scene->circles = init_circle(x,0,100,55);
	// scene->circles->next = init_circle(-100, 0, 0, 50);

	scene->lights = init_light(35,35,35);


	// deprecated.. i think
	// inten = 125000000;
	// scene->lights = init_light(100,150,200, inten);

	// inten = 1250000000;
	// scene->lights->next = init_light(-100,-150,200, inten);
}

void	free_scene(t_scene	*scene)
{
	free_cam(scene->camera);
	free_circle(scene->circles);
	free_light(scene->lights);
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

int main()
{
	t_scene		scene;
	t_mlx_info	mlx;
	int			loop;


	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
	mlx.img.img = NULL;
	loop = 0;
	while (1)
	{
		set_the_scene(&scene, loop);
		get_image(&mlx.img, mlx.mlx);
		kewl_quirky_raytrace(&scene, &mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
		clean_loop(&mlx);
		free_scene(&scene);
		loop += 10;
		if (loop > HEIGHT)
			loop = -1 * HEIGHT;
	}
	mlx_loop(mlx.mlx);
}

// single loop
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