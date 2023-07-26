/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/27 00:21:59 by cshi-xia         ###   ########.fr       */
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
		scene_free(data->scene);
		exit(0);
	}
	return (0);
}