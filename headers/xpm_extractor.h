/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_extractor.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:00:57 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:27:00 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_EXTRACTOR_H

# define XPM_EXTRACTOR_H

# include <stdlib.h>
# include "vec3.h"
# include "mlx_info.h"

typedef struct s_texture
{
	char		*filename;

	t_img_info	data;

	int			width;
	int			height;
}	t_texture;

t_texture		*texture_init(char *filename, void *mlx);
unsigned int	get_xy_rgb(t_texture *txtr, int x, int y);
t_vec3			*get_rgb(t_texture *txtr, double u, double v);
void			free_texture(t_texture **a, void *mlx);

// debug
unsigned int	get_rgb_ui(t_texture *txtr, double u, double v);

#endif