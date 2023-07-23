#include "../headers/lighting.h"

t_vec3	*inverse_color(t_vec3 *c)
{
	int			i;
	matrix_type	i_rgb[3];
	matrix_type	c_stuff[3];

	vec3_store_val(c, c_stuff);
	i = 0;
	while (i < 3)
	{
		i_rgb[i] = absolute(255 - c_stuff[i]);
		++i;
	}
	return (vec3_init_from_array(i_rgb));
}

// a_o_c = absorbed object color
// d_c = object diffuse color
void	calculate_diffuse_color(t_ray *r, t_light *l, t_object *o,
								double costheta)
{
	double	diff_strength;
	t_vec3	*a_o_c;
	t_vec3	*d_c;
	t_vec3	*store[2];

	diff_strength = DIFFUSE_FACTOR;
	a_o_c = inverse_color(o->ob_rgb);
	store[0] = vec3_difference(l->l_rgb, a_o_c, O_CREATE);
	d_c = vec3_scalar_multi(store[0], (costheta * diff_strength), O_CREATE);
	store[1] = vec3_addition(r->d_color, d_c, O_CREATE);
	vec3_free(&d_c);
	vec3_free(&a_o_c);
	vec3_free(&store[0]);
	vec3_free(&r->d_color);
	r->d_color = store[1];
}