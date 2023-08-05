/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/05 18:31:36 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	keypress_event(int key_symbol, t_data *data)
{
	if (key_symbol == 0xff1b) // escape
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