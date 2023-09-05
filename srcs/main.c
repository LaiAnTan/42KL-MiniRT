/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:11 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:36:35 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	do_render_once(t_data *data)
{
	t_timer		*timer;

	timer = timer_init();
	timer_start(timer);
	raytrace(data);
	timer_end(timer);
	timer_print_diff(timer);
	timer_destroy(&timer);
}

int	slapimage(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win,
		data->mlx->cur_img->img, 0, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ERROR);
	data = (t_data *) malloc(sizeof(t_data));
	data->mlx = (t_mlx_info *) malloc(sizeof(t_mlx_info));
	data->mlx->mlx = mlx_init();
	data->mlx->mlx_win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, argv[1]);
	get_image(&data->mlx->img[0], data->mlx->mlx);
	get_image(&data->mlx->img[1], data->mlx->mlx);
	data->mlx->render_img = &data->mlx->img[0];
	data->mlx->cur_img = &data->mlx->img[1];
	data->scene = file_create_scene(argv[1]);
	if (!data->scene)
		return (1);
	get_texture_files(data->scene->sc_objs, data->mlx->mlx);
	scene_print_stats(data->scene);
	change_to_view_port(data->scene);
	do_render_once(data);
	mlx_hook(data->mlx->mlx_win, 17, 0, &clean_exit, data);
	mlx_hook(data->mlx->mlx_win, 2, 0, &keypress_event_mac, data);
	mlx_loop_hook(data->mlx->mlx, slapimage, (void *)data);
	mlx_loop(data->mlx->mlx);
	clean_exit(data);
	return (0);
}

// debug
// int main(int argc, char **argv)
// {
// 	int			loop;
// 	t_timer		*timer;
// 	t_data		data;

// 	if (argc != 2)
// 		return (ERROR);

// 	data.mlx = (t_mlx_info *) malloc(sizeof(t_mlx_info));
// 	printf("Getting RT file..\n");
// 	data.scene = file_create_scene(argv[1]);
// 	if (!data.scene)
// 		return (ERROR);
// 	printf("Done!\n");
// 	data.mlx->mlx = mlx_init();
// 	data.mlx->mlx_win = mlx_new_window(data.mlx->mlx, WIDTH, HEIGHT, argv[1]);
// 	data.mlx->img.img = NULL;
// 	get_image(&data.mlx->img, data.mlx->mlx);

// 	change_to_view_port(data.scene);
// 	scene_print_stats(data.scene);
// 	timer = timer_init();
// 	timer_start(timer);
// 	raytrace(data.scene, data.mlx);
// 	timer_end(timer);
// 	timer_print_diff(timer);
// 	timer_destroy(&timer);

// 	mlx_put_image_to_window(data.mlx->mlx, data.mlx->mlx_win, 
//			data.mlx->img.img, 0, 0);
// 	clean_loop(data.mlx);
// 	sleep(5);
// 	scene_free(data.scene);
// 	mlx_free(data.mlx);
// 	return (0);
// }