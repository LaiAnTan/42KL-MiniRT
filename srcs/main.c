#include "../headers/minirt.h"

// wOw actually ray-tracing!1!!11!11!!
void solve_quad(double *coefficients, double *result)
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
int	intersect_circle(t_ray *ray, t_sphere *sphere)
{
	double	values[3];
	double	coefficients[3];

	// oh yeah set coefficients also based on the notes on your ipad
	// unfortunately you kinda forgot to take into account that 
	// the circle position changes?
	// me cheese this (not sure if works :skull)
	t_vector	*modified_ray_pos;
	t_vector	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, sphere->sp_coords);
	zeroed_pos = v_difference(sphere->sp_coords, sphere->sp_coords);
	// in theory this would work (theory)

	// le ipad formulas
	coefficients[0] = v_magnitude_sqrd(ray->dir_vector);
	coefficients[1] = v_dotproduct(modified_ray_pos, ray->dir_vector) * 2;
	coefficients[2] = v_magnitude_sqrd(modified_ray_pos) - pow(sphere->sp_radius, 2);

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

// # define M_PI 1

// note to myself :-
// this does not work :(
void	calculate_ray_positions(double *store, t_vector *p_vect, int x, int y)
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

	horizontal_angle = fabs(relative_x) * horizontal_angle_per_ray;
	vertical_angle = fabs(relative_y) * vertical_angle_per_ray;

	double	sign_x = (relative_x < 0) ? -1 : 1;
	double	sign_y = (relative_y < 0) ? -1 : 1;

	// this assumes that orientation is (0, 0, 1)
	// and camera is at (0, 0, 0)
	store[0] = ((tan(horizontal_angle * PI / 180) * (WIDTH / 2)) * sign_x) + p_vect->raw_matrix->stuff[0][0];
	store[1] = ((tan(vertical_angle * PI / 180) * (HEIGHT / 2)) * sign_y) + p_vect->raw_matrix->stuff[1][0];
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
t_ray	*project_ray(int x, int y, t_camera *camera)
{
	double		*store;
	t_vector	*pos_vector;
	t_vector	*dir_vector;

	store = get_val(camera->cam_coords);
	calculate_ray_positions(store, camera->cam_coords, x, y);
	pos_vector = init_vector_from_array(store);
	dir_vector = dup_vct(camera->cam_vec_orient);
	free(store);
	return (init_ray(pos_vector, dir_vector));
}

double	calculate_d_from_l(t_ray *r, t_light *l, t_scene *scene)
{
	t_vector	*r_to_l;
	t_ray		*to_light;
	t_sphere	*cur;

	r_to_l = v_difference(l->l_coords, r->pos_vector);
	
	// printf("intesection of ray and circle - vector\n");
	// print_vector(r->pos_vector);
	// printf("\n");

	// printf(" ---- -> rl ---- \n");
	// print_vector(r_to_l);
	// printf("\n");

	cur = scene->sc_spheres;
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

	ret = l->l_brightness / (4 * PI * (mag * mag));
	// printf("return value = %f\n", ret);
	return (ret);
}

void	do_ray_stuff(int x, int y, t_scene *scene, t_mlx_info *mlx)
{
	double		largest_p;
	t_light		*light;
	t_sphere	*cur;
	t_ray		*ray;
	double		p_from_light;

	ray = project_ray(x, y, scene->sc_cameras);
	cur = scene->sc_spheres;
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
		light = scene->sc_lights;
	
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

void	raytrace(t_scene *scene, t_mlx_info *mlx)
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

int main(int argc, char **argv)
{
	t_data		*data;
	int			loop;

	if (argc != 2)
		return (ERROR);
	data = (t_data *) malloc(sizeof(t_data));
	data->mlx = (t_mlx_info *) malloc(sizeof(t_mlx_info));
	data->scene = file_create_scene(argv[1]);
	scene_print_stats(data->scene);
	data->mlx->mlx = mlx_init();
	data->mlx->mlx_win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, argv[1]);
	data->mlx->img.img = NULL;
	loop = 0;
	while (1)
	{
		get_image(&data->mlx->img, data->mlx->mlx);
		raytrace(data->scene, data->mlx);
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img.img, 0, 0);
		clean_loop(data->mlx);
		loop += 10;
		if (loop > WIDTH)
			loop = -1 * WIDTH;
	}
	mlx_loop(data->mlx->mlx);
	scene_free_objects(data->scene);
}