/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:18:06 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 12:30:01 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H

# define LIGHTING_H

# include "minirt.h"

// ambient
void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o);

// diffuse
void	shadow_diffuse(t_ray *ray);
void	calculate_diffuse_color(t_ray *r, t_light *l, t_object *o,
								double costheta);

// specular
void	calculate_specular_color(t_ray *r, t_light *l, t_object *o,
			t_vec3 *light, t_vec3 *normal);

// main
void	diffuse_the_bomb(t_ray *r, t_light *l, t_object *o);
void	calculate_result_color(t_ray *r);

# endif