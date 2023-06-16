#include "minirt.h"

 // ambient coloring
 // ---------------------------------------------------------------------

void	ambient_color(t_ray	*ray, t_ambient *a, t_objects *o)
{
	double		amb_coefficient = AMBIENCE_FACTOR;
	t_vector	*store[2];
	t_vector	*new;

	free_vector(&ray->a_color);
	if (!o)
		ray->a_color = dup_vct(a->color);
	else
	{
		store[0] = v_scalar_multi(a->color, amb_coefficient);
		store[1] = v_scalar_multi(o->color, amb_coefficient);
		ray->a_color = v_addition(store[0], store[1]);
		free_vector(&store[0]);
		free_vector(&store[1]);
	}
}

 // diffuse coloring
 // ---------------------------------------------------------------------

t_vector	*inverse_color(t_vector	*c)
{
	int		i;
	matrix_type	i_rgb[3];
	matrix_type	c_stuff[3];
	
	get_val(c, c_stuff);
	i = 0;
	while (i < 3)
	{
		i_rgb[i] = absolute(255 - c_stuff[i]);
		++i;
	}
	return (init_vector_intarr(i_rgb));
}

void	calculate_diffuse_color(t_ray *r, t_light *l, t_objects *o, double costheta)
{
	double	angles = acos(costheta);
	double	diff_strength = DIFFUSE_FACTOR;

	t_vector	*d_c; // object diffuse color
	t_vector	*a_o_c; // absorbed object color
	t_vector	*store[2];

	a_o_c = inverse_color(o->color);
	store[0] = v_difference(l->color, a_o_c);

	d_c = v_scalar_multi(store[0], (costheta * diff_strength));
	store[1] = v_addition(r->d_color, d_c);

	free_vector(&d_c);
	free_vector(&a_o_c);
	free_vector(&store[0]);
	free_vector(&r->d_color);
	r->d_color = store[1];
}

void	shadow_diffuse(t_ray *ray)
{
	matrix_type	shadow[3] = {0,0,0};
	// hard shadow
	free_vector(&ray->d_color);
	ray->d_color = init_vector_intarr(shadow);
}

void	diffuse_the_bomb(t_ray *r, t_light *l, t_objects *o)
{
	t_vector	*a;
	t_vector	*a_norm;
	t_vector	*b;
	t_vector	*b_norm;

	a = v_difference(l->position, r->pos_vector);
	a_norm = v_get_unit_v(a);

	b = NULL;
	// get normal to intersection
	if (o->type == CIRCLE)
	{
		b = v_difference(r->pos_vector, o->position);
		b_norm = v_get_unit_v(b);
	}
	else if (o->type == PLANE)
		b_norm = dup_vct(o->plane->normal_vect);
	free_vector(&a);
	free_vector(&b);

	double	costheta;
	costheta = v_dotproduct(a_norm, b_norm);
	// printf("angle collided = %.2f\n", (acos(costheta) * 180 / M_PI));

	free_vector(&a_norm);
	free_vector(&b_norm);
	if (costheta < 0)
		shadow_diffuse(r);
	else
		calculate_diffuse_color(r, l, o, costheta);
}

void	calculate_result_color(t_ray *r)
{
	t_vector	*store[2];

	store[0] = v_addition(r->a_color, r->d_color);
	free_vector(&r->color);
	r->color = store[0];
}
