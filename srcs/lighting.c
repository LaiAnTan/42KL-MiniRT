# include "../headers/minirt.h"

 // ambient coloring
 // ---------------------------------------------------------------------

void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o)
{
	vec3_free(&ray->a_color);
	if (o)
		ray->a_color = vec3_multi_each_elem(o->ob_rgb, a->a_strength, O_CREATE);
	else
		ray->a_color = vec3_dup(a->bg_color);
}

 // diffuse coloring
 // ---------------------------------------------------------------------

t_vec3	*inverse_color(t_vec3 *c)
{
	int		i;
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

void	calculate_diffuse_color(t_ray *r, t_light *l, t_object *o, double costheta)
{
	double	diff_strength = DIFFUSE_FACTOR;

	t_vec3	*d_c; // object diffuse color
	t_vec3	*a_o_c; // absorbed object color
	t_vec3	*store[2];

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

// takes in a light-to-object vector and its normal and reflects it
t_vec3	*reflect_light(t_vec3 *light, t_vec3 *normal)
{
	t_vec3	*v;

	v = vec3_scalar_multi(normal, (2 * vec3_dotproduct(light, normal)), O_CREATE);
	vec3_difference(v, light, O_REPLACE);

	return (v);
}

void	calculate_specular_color(t_ray *r, t_light *l, t_object *o, t_vec3 *light, t_vec3 *normal)
{
	double	dot_vr;
	double	specular_exponent;
	double	ks;
	t_vec3	*s_c;
	t_vec3	*dir;
	t_vec3	*reflect;

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
	t_vec3	*spec_col;
	spec_col = vec3_scalar_multi(l->l_rgb, pow(dot_vr, specular_exponent), O_CREATE);

	s_c = vec3_scalar_multi(spec_col, ks, O_CREATE);

	vec3_addition(r->s_color, s_c, O_REPLACE);

	vec3_free(&s_c);
	vec3_free(&dir);
	vec3_free(&reflect);
	vec3_free(&spec_col);
}

void	shadow_diffuse(t_ray *ray)
{
	if (ray->type != SHADOW)
		return ;
	vec3_free(&ray->d_color);
	ray->d_color = vec3_init(0,0,0);
}

void	diffuse_the_bomb(t_ray *r, t_light *l, t_object *o)
{
	t_vec3	*a_norm;
	t_vec3	*b_norm;

	a_norm = vec3_normalize(vec3_difference(l->l_coords, r->pos_vector, O_CREATE), O_REPLACE);

	// get normal to intersection
	if (o->ob_type == CIRCLE)
		b_norm = vec3_normalize(vec3_difference(r->pos_vector, o->ob_coords, O_CREATE), O_REPLACE);
	else if (o->ob_type == PLANE)
		b_norm = vec3_dup(o->ob_planes->pl_vec_normal);
	else if (o->ob_type == CYLINDER)
		b_norm = calc_cylinder_norm(r, o);
	else if (o->ob_type == CONE)
		b_norm = calc_cone_norm(r, o); 

	double	costheta;
	costheta = vec3_dotproduct(a_norm, b_norm);
	// wow im sure am lazy to recalculate the costheta angle for the opposite normal for planes
	if (o->ob_type == PLANE && costheta < 0)
		costheta *= -1;
	// else if (o->ob_type == CYLINDER && costheta < 0)
	// 	costheta *= -1;

	if (costheta < 0)
	{
		shadow_diffuse(r);
	}
	else
	{
		r->type = COLLIDED;
		calculate_diffuse_color(r, l, o, costheta);
		calculate_specular_color(r, l, o, a_norm, b_norm);
	}
	vec3_free(&a_norm);
	vec3_free(&b_norm);
}

void	calculate_result_color(t_ray *r)
{
	r->color = vec3_addition(r->a_color, r->d_color, O_CREATE);
	vec3_addition(r->color, r->s_color, O_REPLACE);
}
