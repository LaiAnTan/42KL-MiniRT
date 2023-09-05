/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 14:27:42 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// 0xff1b = ESC
// 0x72 = r
int	keypress_event(int key_symbol, t_data *data)
{
	if (key_symbol == 53)
	{
		printf("ESC pressed, exiting...");
		clean_exit(data);
	}
	if (key_symbol == 15)
	{
		printf("R pressed, commencing re-render of image...");
		do_render_once(data);
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win,
		data->mlx->cur_img->img, 0, 0);
	}
	return (0);
}
