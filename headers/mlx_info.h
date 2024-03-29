/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:00:34 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:28:29 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INFO_H

# define MLX_INFO_H

# if __linux__
#  include <X11/X.h>
#  include "../mlx_linux/mlx.h"
# elif __APPLE__
#  include <mlx.h>
# endif

typedef struct s_img_info
{
	void	*img;

	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	*addr;
}	t_img_info;

typedef struct s_mlx_info
{
	void			*mlx;
	void			*mlx_win;

	t_img_info		img[2];
	t_img_info		*cur_img;
	t_img_info		*render_img;
}	t_mlx_info;

#endif