#include "../headers/minirt.h"

// prod
// int	render(void *rt)
// {
// 	t_data		*data;
// 	t_timer		*timer;

// 	data = (t_data *)rt;
// 	data->mlx->img.img = NULL;
// 	get_image(&data->mlx->img, data->mlx->mlx);

// 	timer = timer_init();
// 	timer_start(timer);
// 	raytrace(data->scene, data->mlx);
// 	timer_end(timer);
// 	timer_print_diff(timer);
// 	timer_destroy(&timer);

// 	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img.img, 0, 0);
// 	clean_loop(data->mlx);
// }

// int main(int argc, char **argv)
// {
// 	t_data		*data;

// 	if (argc != 2)
// 		return (ERROR);
// 	data = (t_data *) malloc(sizeof(t_data));
// 	data->mlx = (t_mlx_info *) malloc(sizeof(t_mlx_info));
// 	printf("Getting RT file..\n");
// 	data->scene = file_create_scene(argv[1]);
// 	printf("Done!\n");
// 	scene_print_stats(data->scene);
// 	data->mlx->mlx = mlx_init();
// 	data->mlx->mlx_win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, argv[1]);
// 	mlx_key_hook(data->mlx->mlx_win, keypress_event, data);
// 	mlx_loop_hook(data->mlx->mlx, render, (void *)data);
// 	mlx_loop(data->mlx->mlx);
// 	scene_free(data->scene);
// 	return (0);
// }

// // debug
int main(int argc, char **argv)
{
	int			loop;
	t_timer		*timer;
	t_data		data;

	if (argc != 2)
		return (ERROR);
	
	data.mlx = (t_mlx_info *) malloc(sizeof(t_mlx_info));
	printf("Getting RT file..\n");
	data.scene = file_create_scene(argv[1]);
	printf("Done!\n");
	scene_print_stats(data.scene);
	data.mlx->mlx = mlx_init();
	data.mlx->mlx_win = mlx_new_window(data.mlx->mlx, WIDTH, HEIGHT, argv[1]);
	data.mlx->img.img = NULL;
	get_image(&data.mlx->img, data.mlx->mlx);

	timer = timer_init();
	timer_start(timer);
	raytrace(data.scene, data.mlx);
	timer_end(timer);
	timer_print_diff(timer);
	timer_destroy(&timer);

	mlx_put_image_to_window(data.mlx->mlx, data.mlx->mlx_win, data.mlx->img.img, 0, 0);
	clean_loop(data.mlx);
	sleep(5);
	scene_free(data.scene);
	mlx_free(data.mlx);
	return (0);
}

// test view matrices
// delete once done

// int main(void)
// {
// 	t_cylinder cy;

// 	cy.cy_coords = vec4_init(-50, 0, 20, 1);
// 	cy.cy_vec_axis = vec4_init(0, 1, 0, 1);

// 	printf("cylinder coords\n");
// 	vec4_print(cy.cy_coords);
// 	printf("cylinder axis vector\n");
// 	vec4_print(cy.cy_vec_axis);

// 	t_matrix *model_matrix = get_model_matrix(&cy);
// 	printf("model_matrix = \n");
// 	m_print_matrix(model_matrix);
// 	t_matrix *inv_model_matrix = get_inverse_transform(model_matrix);
// 	printf("inverse model matrix = \n");
// 	m_print_matrix(inv_model_matrix);

// }
