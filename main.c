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

	// printf("%f, %f, %f\n", values[0], values[1], values[2]);

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

	values[0] = fmin(values[1], values[2]);
	if (values[0] < 0)
		values[0] = fmax(values[1], values[2]);

	store[0] = v_scalar_multi(ray->dir_vector, values[0]);
	store[1] = dup_vct(ray->pos_vector);
	free_vector(&ray->pos_vector);
	ray->pos_vector = v_addition(store[1], store[0]);

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

// # define M_PI 1

// note to myself :-
// this does not work :(
void	calculate_ray_positions(double *store, t_vector *p_vect, t_vector *o_vect, int x, int y)
{
	float		horifov;
	float		vertifov;
	float		width;
	float		height;

	double		relative_x;
	double		relative_y;
	double		horizontal_angle_per_ray;
	double		vertical_angle_per_ray;

	horifov = HORIFOV;
	vertifov = VERTIFOV;
	width = WIDTH;
	height = HEIGHT;

	horizontal_angle_per_ray = horifov / width;
	vertical_angle_per_ray = vertifov / height;

	// printf("%f, %f\n", horizontal_angle_per_ray, vertical_angle_per_ray);

	relative_x = x - (width / 2);
	relative_y = (height / 2) - y;

	double	horizontal_angle;
	double	vertical_angle;

	horizontal_angle = absolute(relative_x) * horizontal_angle_per_ray;
	vertical_angle = absolute(relative_y) * vertical_angle_per_ray;

	double	sign_x = (relative_x < 0) ? -1 : 1;
	double	sign_y = (relative_y < 0) ? -1 : 1;

	// this assumes that orientation is (0, 0, 1)
	// and camera is at (0, 0, 0)
	store[0] = ((tan(horizontal_angle * M_PI / 180) * (WIDTH / 2)) * sign_x) + p_vect->raw_matrix->stuff[0][0];
	store[1] = ((tan(vertical_angle * M_PI / 180) * (HEIGHT / 2)) * sign_y) + p_vect->raw_matrix->stuff[1][0];
	store[2] = 0;
}

// void	calculate_ray_positions(double *store, t_vector *o_vect, int x, int y)
// {
// 	double		*vect_val;

// 	vect_val = get_val(o_vect);

// 	store[0] = x;
// 	store[1] = y;
// 	// vx x + vy y + vz z = 0 <--- all vector perpendicular to that camera point
// 	store[2] = ( -1 * ( (vect_val[0] * x) + (vect_val[1] * y) )) / vect_val[2];
// 	free(vect_val);
// }

// projects a ray
t_ray	*project_ray(int x, int y, t_cam *camera)
{
	double		*store;
	t_vector	*pos_vector;
	t_vector	*dir_vector;

	store = get_val(camera->position);
	calculate_ray_positions(store, camera->position, camera->orientation, x, y);
	pos_vector = init_vector_intarr(store);
	dir_vector = dup_vct(camera->orientation);
	free(store);
	return (init_ray(pos_vector, dir_vector));
}

double	calculate_d_from_l(t_ray *r, t_light *l, t_scene *scene)
{
	t_vector	*r_to_l;
	t_ray		*to_light;
	t_circle	*cur;

	r_to_l = v_difference(l->position, r->pos_vector);
	
	// printf("intesection of ray and circle - vector\n");
	// print_vector(r->pos_vector);
	// printf("\n");

	// printf(" ---- -> rl ---- \n");
	// print_vector(r_to_l);
	// printf("\n");

	cur = scene->circles;
	while (cur)
	{
		to_light = dup_ray(r);
		free_vector(&to_light->dir_vector);
		to_light->dir_vector = v_normalize(r_to_l);
		free_vector(&to_light->pos_vector);
		to_light->pos_vector = v_addition(r->pos_vector, to_light->dir_vector);

		// printf(" --- pos vector ---- \n");
		// print_vector(to_light->pos_vector);
		// printf(" ---- dir vector ---- \n");
		// print_vector(to_light->dir_vector);
		// printf("\n");

		if (intersect_circle(to_light, cur) == SUCCESS)
		{
			free_vector(&r_to_l);
			free_ray(&to_light);
			return (ERROR);
		}
		free_ray(&to_light);
		cur = cur->next;
	}

	// doesnt intersect any circle, calculate distance
	double		mag;

	mag = v_magnitude(r_to_l);
	free_vector(&r_to_l);

	double	ret;

	ret = l->intensity / (4 * M_PI * (mag * mag));
	// printf("return value = %f\n", ret);
	return (ret);
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
				ray->type = COLLIDED;
			if (p_from_light > largest_p)
				largest_p = p_from_light;
			light = light->next;
		}

	}

	if (ray->type == COLLIDED)
	{
		// printf("Collided with circle\n");
		write_pixel(&mlx->img, x, y, create_trgb(largest_p , 0, 0));
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
	double	inten;
	scene->camera = init_cam();
	scene->circles = init_circle(x,0,0,50);
	// scene->circles->next = init_circle(-100, 0, 0, 50);
	inten = 125000000;
	scene->lights = init_light(100,150,200, inten);
	// inten = 1250000000;
	// scene->lights->next = init_light(-100,-150,200, inten);
}

void	free_scene(t_scene	*scene)
{
	free_cam(scene->camera);
	free_circle(scene->circles);
	free_light(scene->lights);
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
		if (loop > WIDTH)
			loop = -1 * WIDTH;
	}
	mlx_loop(mlx.mlx);
}

// int main()
// {
// 	t_scene		scene;
// 	t_mlx_info	mlx;
// 	int			loop;

// 	loop = 0;
// 	set_the_scene(&scene);
// 	kewl_quirky_raytrace(&scene, &mlx);
// }