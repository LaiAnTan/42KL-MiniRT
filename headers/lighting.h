/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:18:06 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/05 18:46:47 by cshi-xia         ###   ########.fr       */
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

// get object color based on uv or something idk :(
t_vec3	*get_object_color(t_ray *ray, t_object *o);

# endif