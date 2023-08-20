/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/20 12:37:27 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// 0xff1b = ESC
// 0x72 = r
int	keypress_event(int key_symbol, t_data *data)
{
	if (key_symbol == 0xff1b)
	{
		printf("ESC pressed, exiting...");
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
		// mlx_destroy_display(data->mlx->mlx);
		scene_free(data->scene, data->mlx->mlx);
		exit(0);
	}
	if (key_symbol == 0x72)
		do_render_once(data);
	return (0);
}
