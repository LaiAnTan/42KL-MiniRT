# include "../headers/minirt.h"

t_object	*get_closest_object(t_ray *ray, t_scene *scene, int closest,
		double	*k_val)
{
	t_object	*cur;
	t_object	*closest_object_src;
	double		closest_object;
	double		r_to_o;

	cur = scene->sc_objs;
	closest_object = INFINITY;
	closest_object_src = NULL;
	while (cur)
	{
		if (cur->ob_type == CIRCLE)
			r_to_o = intersect_circle(ray, cur);
		else if (cur->ob_type == PLANE)
			r_to_o = intersect_plane(ray, cur);
		else if (cur->ob_type == CYLINDER)
			r_to_o = intersect_cylinder(ray, cur);

		// means collided d
		if (r_to_o != ERROR)
		{
			if (!closest)
				return (cur);
			if (r_to_o < closest_object)
			{
				closest_object = r_to_o;
				closest_object_src = cur;
			}
		}
		cur = cur->next;
	}
	if (k_val)
		*k_val = closest_object;
	return (closest_object_src);
}

int	get_closest_light(t_ray *r, t_light *l, t_scene *scene)
{
	t_vec3		*r_to_l;
	t_ray		*to_light;
	t_object	*collided_obj;

	r_to_l = vec3_difference(l->l_coords, r->pos_vector);

	to_light = dup_ray(r);
	vec3_free(&to_light->dir_vector);
	to_light->dir_vector = vec3_normalize(r_to_l);
	vec3_free(&to_light->pos_vector);
	to_light->pos_vector = vec3_addition(r->pos_vector, to_light->dir_vector);

	collided_obj = get_closest_object(to_light, scene, 0, NULL);
	vec3_free(&r_to_l);
	free_ray(&to_light);

	if (collided_obj == NULL)
		return (SUCCESS);
	return (ERROR);
}
