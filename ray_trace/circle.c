#include "minirt.h"

void solve_quad(double	*coefficients, double *result)
{
	double	a;
	double	b;
	double	c;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];

	// walao make a bzero nia
	for (int i = 0; i < 3; ++i)
		result[i] = 0;

	result[0] = (b * b) - ( 4 * a * c );
	// determinant is less than zero
	if (result[0] < 0)
		return ;
	result[1] = ((-1 * b) + sqrt(result[0])) / (2 * a);
	result[2] = ((-1 * b) - sqrt(result[0])) / (2 * a);
}

// ax^2 + bx + c
double	intersect_circle(t_ray	*ray, t_objects *o)
{
	double	values[3];
	double	coefficients[3];
	double	mag;

	// me cheese this (not sure if works :skull)
	t_vector	*modified_ray_pos;
	t_vector	*zeroed_pos;

	modified_ray_pos = v_difference(ray->pos_vector, o->position);
	zeroed_pos = v_difference(o->position, o->position);
	// in theory this would work (theory)

	// le ipad formulas
	coefficients[0] = v_magnitude_sqrd(ray->dir_vector);
	coefficients[1] = v_dotproduct(modified_ray_pos, ray->dir_vector) * 2;
	coefficients[2] = v_magnitude_sqrd(modified_ray_pos) - (o->circle->radius * o->circle->radius);

	solve_quad(coefficients, values);
	free_vector(&modified_ray_pos);
	free_vector(&zeroed_pos);

	if (values[0] < 0)
		return (ERROR);
	if (values[1] < 0 && values[2] < 0)
		return (ERROR);

	values[0] = fmin(values[1], values[2]);
	if (values[0] < 0)
		values[0] = fmax(values[1], values[2]);

	return (values[0]);
}
