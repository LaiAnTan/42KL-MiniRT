/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:00:38 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:16:40 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"
# include "vec4.h"

/* Ray Types */
# define LIGHT 0
# define COLLIDED 1
# define SHADOW	2

// a_color = ambient
// d_color = diffuse
// s_color = specular
typedef struct s_ray
{
	int			inside;

	t_vec3		*pos_vector;

	t_vec3		*dir_vector;

	t_vec3		*color;
	t_vec3		*a_color;
	t_vec3		*d_color;
	t_vec3		*s_color;
}	t_ray;

t_ray	*init_ray(t_vec3 *pos_vector, t_vec3 *dir_vector);
void	free_ray(t_ray **ray);
void	move_ray(t_ray *ray, double k);
t_ray	*dup_ray(t_ray *source);

#endif