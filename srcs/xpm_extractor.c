/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:37:55 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:03:12 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/xpm_extractor.h"

// creates a image based on the xlm file given and returns it
// MAKE SURE FILENAME IS MALLOCED
t_texture	*texture_init(char *filename, void *mlx_ptr)
{
	t_texture	*ret;
	t_img_info	*temp;

	ret = malloc(sizeof(t_texture));
	ret->filename = filename;
	ret->data.img = mlx_xpm_file_to_image(mlx_ptr, filename, &ret->width,
			&ret->height);
	if (!ret->data.img)
	{
		printf("oopsie something went wrong :(\n");
		free(ret->filename);
		return (NULL);
	}
	temp = &ret->data;
	temp->addr = mlx_get_data_addr(temp->img, &temp->bits_per_pixel,
			&temp->line_length, &temp->endian);
	return (ret);
}

// gets the rgb value of the texture at point x and y
unsigned int	get_xy_rgb(t_texture *txtr, int x, int y)
{
	t_img_info	*pntr;
	char		*dst;

	pntr = &txtr->data;
	dst = pntr->addr + (y * pntr->line_length + x * (pntr->bits_per_pixel / 8));
	return (*((unsigned *)dst));
}

// gets the rgb value on a point, returns in t_vec3 format
// uv range between [0, 1]
// psa use below for range -1 to 1
// x = round((txtr->width / 2) * (1 + u));
// y = round((txtr->height / 2) * (1 + v));
unsigned int	get_rgb_ui(t_texture *txtr, double u, double v)
{
	int				x;
	int				y;
	unsigned int	rgb;

	x = round(txtr->width * u);
	y = round(txtr->height * v);
	rgb = get_xy_rgb(txtr, x, y);
	return (rgb);
}

// gets the rgb value on a point, returns in t_vec3 format
// uv range between [0, 1]
// we dont need to care about transparancy
// store array: 0, 1, 2 = r, g, b
t_vec3	*get_rgb(t_texture *txtr, double u, double v)
{
	unsigned int	rgb;
	t_matrix_type		store[3];

	rgb = get_rgb_ui(txtr, u, v);
	store[0] = (t_matrix_type)(int)((rgb >> 16) & 0xFF);
	store[1] = (t_matrix_type)(int)((rgb >> 8) & 0xFF);
	store[2] = (t_matrix_type)(int)(rgb & 0xFF);
	return (vec3_init_from_array(store));
}

void	free_texture(t_texture **a, void *mlx)
{
	if (!(*a))
		return ;
	free((*a)->filename);
	mlx_destroy_image(mlx, (*a)->data.img);
	free((*a));
	(*a) = NULL;
}
