/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:18:06 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/19 19:00:23 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H

# define LIGHTING_H

# include "minirt.h"

// ambient
void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o);

// diffuse
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
void	calculate_ray_color(t_ray *ray, t_light *light, t_object *objs, 
	t_object *closest);

# endif