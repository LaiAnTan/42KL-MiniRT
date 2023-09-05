/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:32:00 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 17:38:56 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	destory_images(t_mlx_info *mlx)
{
	if (mlx->img[0].img != NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->img[0].img);
		mlx->img[0].img = NULL;
	}
	if (mlx->img[1].img != NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->img[1].img);
		mlx->img[1].img = NULL;
	}
}

int	clean_exit(t_data *data)
{
	if (data->mlx->mlx_win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
	destory_images(data->mlx);
	data->scene = scene_free(data->scene, data->mlx->mlx);
	exit(0);
	return (0);
}
