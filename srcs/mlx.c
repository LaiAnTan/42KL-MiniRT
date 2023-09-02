/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:56 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/02 10:28:28 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

void	get_image(t_img_info *img_info, void *mlx)
{
	img_info->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_info->addr = mlx_get_data_addr(img_info->img, &img_info->bits_per_pixel,
			&img_info->line_length, &img_info->endian);
}

// disabled temporarily
// void	clean_loop(t_mlx_info *mlx)
// {
// 	if (mlx->img->img != NULL)
// 	{
// 		mlx_destroy_image(mlx->mlx, mlx->img->img);
// 		mlx->img->img = NULL;
// 	}
// }

void	write_pixel(t_img_info *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	create_trgb(t_vec3 *color)
{
	int	r;
	int	g;
	int	b;

	r = color->raw_matrix->m[0][0];
	g = color->raw_matrix->m[1][0];
	b = color->raw_matrix->m[2][0];
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (0 << 24 | r << 16 | g << 8 | b);
}

// quite hilariously, dont exists in imac
void	mlx_free(t_mlx_info *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	// mlx_destroy_display(data->mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}
