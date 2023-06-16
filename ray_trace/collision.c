#include "minirt.h"

t_objects	*get_closest_object(t_ray *ray, t_scene *scene, int closest, double	*k_val)
{
	t_objects	*cur;
	t_objects	*closest_object_src;
	double		closest_object;
	double		r_to_o;

	cur = scene->objs;
	closest_object = INFINITY;
	closest_object_src = NULL;
	while (cur)
	{
		if (cur->type == CIRCLE)
			r_to_o = intersect_circle(ray, cur);
		else if (cur->type == PLANE)
			r_to_o = intersect_plane(ray, cur);

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
	t_vector	*r_to_l;
	t_ray		*to_light;
	t_objects	*collided_obj;

	r_to_l = v_difference(l->position, r->pos_vector);

	to_light = dup_ray(r);
	free_vector(&to_light->dir_vector);
	to_light->dir_vector = v_get_unit_v(r_to_l);
	free_vector(&to_light->pos_vector);
	to_light->pos_vector = v_addition(r->pos_vector, to_light->dir_vector);

	collided_obj = get_closest_object(to_light, scene, 0, NULL);
	free_vector(&r_to_l);
	free_ray(&to_light);

	if (collided_obj == NULL)
		return (SUCCESS);
	return (ERROR);
}
