#include "../headers/lighting.h"

// takes in a light-to-object vector and its normal and reflects it
static t_vec3	*reflect_light(t_vec3 *light, t_vec3 *normal)
{
	t_vec3	*v;

	v = vec3_scalar_multi(normal, (2 * vec3_dotproduct(light, normal)),
			O_CREATE);
	vec3_difference(v, light, O_REPLACE);
	return (v);
}

// specular color
void	calculate_specular_color(t_ray *r, t_light *l, t_object *o,
			t_vec3 *light, t_vec3 *normal)
{
	double	dot_vr;
	double	specular_exponent;
	double	ks;
	t_vec3	*s_c;
	t_vec3	*dir;
	t_vec3	*reflect;
	t_vec3	*spec_col;

	if (o->ob_spec <= 0)
		return ;
	specular_exponent = o->ob_spec;
	ks = 0.24f * log(0.14f * o->ob_spec) + 0.6f;
	reflect = reflect_light(light, normal);
	dir = vec3_dup(r->dir_vector);
	vec3_negate(dir);
	dot_vr = vec3_dotproduct(reflect, dir);
	if (dot_vr < 0)
	{
		vec3_free(&reflect);
		vec3_free(&dir);
		return ;
	}
	spec_col = vec3_scalar_multi(l->l_rgb,
			pow(dot_vr, specular_exponent), O_CREATE);
	s_c = vec3_scalar_multi(spec_col, ks, O_CREATE);
	vec3_addition(r->s_color, s_c, O_REPLACE);
	vec3_free(&s_c);
	vec3_free(&dir);
	vec3_free(&reflect);
	vec3_free(&spec_col);
}