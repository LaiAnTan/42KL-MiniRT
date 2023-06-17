# include "../headers/minirt.h"

 // ambient coloring
 // ---------------------------------------------------------------------

void	ambient_color(t_ray	*ray, t_ambient *a, t_object *o)
{
	vec3_free(&ray->a_color);
	if (o)
	{
		ray->a_color = vec3_multi_each_elem(o->ob_rgb, a->a_strength);
		vec3_print(ray->a_color);
	}
	else
		ray->a_color = vec3_dup(a->bg_color);
}

 // diffuse coloring
 // ---------------------------------------------------------------------

t_vec3	*inverse_color(t_vec3	*c)
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
	double	angles = acos(costheta);
	double	diff_strength = DIFFUSE_FACTOR;

	t_vec3	*d_c; // object diffuse color
	t_vec3	*a_o_c; // absorbed object color
	t_vec3	*store[2];

	a_o_c = inverse_color(o->ob_rgb);
	store[0] = vec3_difference(l->l_rgb, a_o_c);

	d_c = vec3_scalar_multi(store[0], (costheta * diff_strength));
	store[1] = vec3_addition(r->d_color, d_c);

	vec3_free(&d_c);
	vec3_free(&a_o_c);
	vec3_free(&store[0]);
	vec3_free(&r->d_color);
	r->d_color = store[1];
}

void	shadow_diffuse(t_ray *ray)
{
	matrix_type	shadow[3] = {0,0,0};
	// hard shadow

	if (ray->type != SHADOW)
		return ;
	vec3_free(&ray->d_color);
	ray->d_color = vec3_init_from_array(shadow);
}

void	diffuse_the_bomb(t_ray *r, t_light *l, t_object *o)
{
	t_vec3	*a;
	t_vec3	*a_norm;
	t_vec3	*b;
	t_vec3	*b_norm;

	a = vec3_difference(l->l_coords, r->pos_vector);
	a_norm = vec3_normalize(a);

	b = NULL;
	// get normal to intersection
	if (o->ob_type == CIRCLE)
	{
		b = vec3_difference(r->pos_vector, o->ob_coords);
		b_norm = vec3_normalize(b);
	}
	else if (o->ob_type == PLANE)
		b_norm = vec3_dup(o->ob_planes->pl_vec_normal);
	vec3_free(&a);
	vec3_free(&b);

	double	costheta;
	costheta = vec3_dotproduct(a_norm, b_norm);
	// printf("angle collided = %.2f\n", (acos(costheta) * 180 / M_PI));

	vec3_free(&a_norm);
	vec3_free(&b_norm);
	if (costheta < 0)
	{
		shadow_diffuse(r);
	}
	else
	{
		r->type = COLLIDED;
		calculate_diffuse_color(r, l, o, costheta);
	}
}

void	calculate_result_color(t_ray *r)
{
	t_vec3	*store[2];

	store[0] = vec3_addition(r->a_color, r->d_color);
	vec3_free(&r->color);
	r->color = store[0];
}
