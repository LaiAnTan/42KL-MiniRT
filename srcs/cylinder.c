#include "../headers/minirt.h"

// need a specific center bottom getter (since the cylinder axis isnt constantly 0,0,1)
t_vec3	*get_centre_bottom(t_vec3 *center, t_object *o)
{
	double	diff;
	t_vec3	*ret;
	t_vec3	*to_min;

	diff = o->ob_cylinders->cy_height / 2;
	to_min = vec3_scalar_multi(o->ob_cylinders->cy_vec_axis, diff);
	ret = vec3_difference(center, to_min);
	vec3_free(&to_min);
	return (ret);
}

// when used, r is already at intersection point
t_vec3	*calc_cylinder_norm(t_ray *r, t_object *o)
{
	t_vec3	*bottom;

	bottom = get_centre_bottom(o->ob_coords, o);

	t_vec3	*modified_ray;

	modified_ray = vec3_difference(r->pos_vector, bottom);

	t_vec3	*proj_ray;

	proj_ray = vec3_projection(modified_ray, o->ob_cylinders->cy_vec_axis);

	t_vec3	*norm;

	norm = vec3_difference(modified_ray, proj_ray);
	
	t_vec3	*ret;

	ret = vec3_normalize(norm);

	vec3_free(&bottom);
	vec3_free(&norm);
	vec3_free(&proj_ray);
	vec3_free(&modified_ray);
	// return (ret);
	if (r->inside == 0)
		return (ret);
	else
		return (vec3_negate(ret));
}

void	solve_quad_cy(double *coefficients, double *result)
{
	double	a;
	double	b;
	double	c;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];

	result[0] = (b * b) - (a * c);
	// determinant is less than zero
	if (result[0] < 0)
		return;

	double d;
	d = sqrt(result[0]);

	result[1] = ((-1 * b) + d) / (a);
	result[2] = ((-1 * b) - d) / (a);
}

void	swap(double *a, double *b)
{
	double	temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

double	test_intersect(t_ray *ray, t_object *o, t_vec3 *modified_ray_pos, t_vec3 *center_bottom, double value[2])
{
	t_vec3	*intersect;
	t_vec3	*mover;
	t_vec3	*diff;
	t_vec3	*h;

	int	i;
	int	k;

	// rearrange values
	if (value[0] > value[1])
		swap(&value[0], &value[1]);

	i = 0;
	// h = vec3_scalar_multi(o->ob_cylinders->cy_vec_axis, o->ob_cylinders->cy_height);
	while (i < 2)
	{
		if (value[i] < 0)
		{
			++i;
			continue;
		}
		mover = vec3_scalar_multi(ray->dir_vector, value[i]);
	
		intersect = vec3_addition(modified_ray_pos, mover);
		vec3_free(&mover);

		diff = vec3_difference(intersect, center_bottom);
		vec3_free(&intersect); 

		k = vec3_dotproduct(diff, o->ob_cylinders->cy_vec_axis);
		// k = vec3_dotproduct(diff, h);
		vec3_free(&diff);

		if (k >= 0 && k <= o->ob_cylinders->cy_height)
		{
			vec3_free(&modified_ray_pos);
			vec3_free(&center_bottom);
			if (i == 1)
				ray->inside = 1;
			return (value[i]);
		}
		++i;
	}
	vec3_free(&modified_ray_pos);
	vec3_free(&center_bottom);
	return (ERROR);
}

double    intersect_cylinder(t_ray *ray, t_object *o)
{
	double	values[3];
	double	coefficients[3];

	t_vec3	*modified_ray_pos;
	t_vec3	*center_bottom;
	t_vec3	*w;

    modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords);

	t_vec3	*zeroed_pos = vec3_init(0,0,0);
	center_bottom = get_centre_bottom(zeroed_pos, o);
    // center_bottom = vec3_dup(o->ob_coords);
    // center_bottom->raw_matrix->m[2][0] -= o->ob_cylinders->cy_height / 2;
    w = vec3_difference(modified_ray_pos, center_bottom);

	coefficients[0] = 1 - 
					(vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis));

    coefficients[1] = (vec3_dotproduct(ray->dir_vector, w) -
                        vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) *
                            vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis));

    coefficients[2] = vec3_dotproduct(w, w) - 
						(vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis)) -
                        ((o->ob_cylinders->cy_diameter / 2) * (o->ob_cylinders->cy_diameter / 2));
						
    solve_quad_cy(coefficients, values);

	// printf("\n");
    if (values[0] < 0)
        return (ERROR);
    if (values[1] < 0 && values[2] < 0)
        return (ERROR);

	return (test_intersect(ray, o, modified_ray_pos, center_bottom, &values[1]));	
}