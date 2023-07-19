#include "../headers/minirt.h"

// when used, r is already at intersection point
t_vec3	*calc_cylinder_norm(t_ray *r, t_object *o)
{
	t_vec3	*modified_ray;
	t_vec3	*proj_ray;

	modified_ray = vec3_difference(r->pos_vector, o->ob_cylinders->cy_bottom, O_CREATE);
	proj_ray = vec3_projection(modified_ray, o->ob_cylinders->cy_vec_axis, O_CREATE);

	// shitshow of a calculation (answer is inside modified_ray)
	// -- i hate this
	vec3_normalize(vec3_difference(modified_ray, proj_ray, O_REPLACE), O_REPLACE);

	vec3_free(&proj_ray);
	if (r->inside == 0)
		return (modified_ray);
	else
		return (vec3_negate(modified_ray));
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

double	cy_test_intersect(t_ray *ray, t_object *o, double value[2])
{
	t_vec3	*intersect;
	t_vec3	*mover;
	t_vec3	*diff;
	t_vec3	*h;
	int		i;
	double	k;

	if (value[0] > value[1])
		swap(&value[0], &value[1]);
	i = 0;
	while (i < 2)
	{
		if (value[i] >= 0)
		{
			mover = vec3_scalar_multi(ray->dir_vector, value[i], O_CREATE);
			intersect = vec3_addition(ray->pos_vector, mover, O_CREATE);

			vec3_free(&mover);

			// problematic one liner 2
			k = vec3_dotproduct(vec3_difference(intersect, o->ob_cylinders->cy_bottom, O_REPLACE), o->ob_cylinders->cy_vec_axis);

			vec3_free(&intersect);

			if (k >= 0 && k <= o->ob_cylinders->cy_height)
			{
				if (i == 1)
					ray->inside = 1;
				return (value[i]);
			}
		}
		++i;
	}
	return (ERROR);
}

double    intersect_cylinder(t_ray *ray, t_object *o)
{
	double	r;
	double	values[3];
	double	coefficients[3];
	t_vec3	*w;
	r = o->ob_cylinders->cy_diameter / 2;
    w = vec3_difference(ray->pos_vector, o->ob_cylinders->cy_bottom, O_CREATE);

	coefficients[0] = 1 - 
					(vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis));

    coefficients[1] = (vec3_dotproduct(ray->dir_vector, w) -
                        vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) *
                            vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis));

    coefficients[2] = vec3_dotproduct(w, w) - 
						(vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis)) -
                        (r * r);
	vec3_free(&w);
    solve_quad_cy(coefficients, values);

    if (values[0] < 0)
        return (ERROR);
    if (values[1] < 0 && values[2] < 0)
        return (ERROR);
	return (cy_test_intersect(ray, o, &values[1]));	
}