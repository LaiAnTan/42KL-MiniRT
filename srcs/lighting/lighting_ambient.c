#include "../headers/lighting.h"

void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o)
{
	vec3_free(&ray->a_color);
	if (o)
		ray->a_color = vec3_multi_each_elem(o->ob_rgb, a->a_strength, O_CREATE);
	else
		ray->a_color = vec3_dup(a->bg_color);
}