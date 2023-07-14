#include "../headers/minirt.h"

void	solve_quad_cn(double *coefficients, double *result)
{
	double	a;
	double	b;
	double	c;

	a = coefficients[0];
	b = coefficients[1];
	c = coefficients[2];

	result[0] = (b * b) - (4 * a * c);
	// determinant is less than zero
	if (result[0] < 0)
		return;

	double d;
	d = sqrt(result[0]);

	result[1] = ((-1 * b) + d) / (2 * a);
	result[2] = ((-1 * b) - d) / (2 * a);
}

// thanks for the website HEHEHHE
double	intersect_cone(t_ray *ray, t_object *o)
{
	double	values[3];
	double	coefficients[3];
	double	r;
	double	constant;

	t_vec3	*modified_pos;

	modified_pos = vec3_difference(ray->pos_vector, o->ob_coords);

	r = o->ob_cones->cn_diameter / 2;
	constant = (r * r) / (o->ob_cones->cn_height * o->ob_cones->cn_height);

	double	dp1 = vec3_dotproduct(o->ob_cones->cn_vec_axis, ray->dir_vector);
	double	dp2 = vec3_dotproduct(o->ob_cones->cn_vec_axis, modified_pos);

	coefficients[0] = 1 - ((constant + 1) * dp1);
	coefficients[1] = 2 * (
							vec3_dotproduct(modified_pos, ray->dir_vector) - 
							((constant + 1) * dp1 * dp2)
						);
	coefficients[2] = vec3_dotproduct(modified_pos, modified_pos) - 
						((constant + 1) * dp2);

	solve_quad_cn(coefficients, values);

    vec3_free(&modified_pos);

    if (values[0] < 0)
        return (ERROR);
    if (values[1] < 0 && values[2] < 0)
        return (ERROR);

    values[0] = fmin(values[1], values[2]);
    if (values[0] < 0)
        values[0] = fmax(values[1], values[2]);

    return (values[0]);
}