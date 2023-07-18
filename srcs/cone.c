#include "../headers/minirt.h"

// when used, r is already at intersection point
t_vec3	*calc_cone_norm(t_ray *r, t_object *o)
{
	// no idea if it will work
	if (vec3_isequal(r->pos_vector, o->ob_coords))
		return (vec3_dup(o->ob_cones->cn_vec_axis));

	t_vec3	*point_to_top;
	t_vec3	*point_to_center;
	t_vec3	*criss_cross;
	t_vec3	*ret;

	point_to_top = vec3_difference(o->ob_coords, r->pos_vector, O_CREATE);
	point_to_center = vec3_difference(o->ob_cones->cn_bottom, r->pos_vector, O_CREATE);
	criss_cross = vec3_crossproduct(point_to_top, point_to_center, O_CREATE);

	vec3_free(&point_to_center);

	ret = vec3_normalize(vec3_crossproduct(point_to_top, criss_cross, O_REPLACE), O_REPLACE);
	
	vec3_free(&criss_cross);

	if (r->inside == 0)
		return (ret);
	else
		return (vec3_negate(ret));
}

void	solve_quad_cn(double *coefficients, double *result)
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

double	cn_test_intersect(t_ray *ray, t_object *o, double value[2])
{
	t_vec3	*intersect;
	t_vec3	*mover;
	t_vec3	*diff;
	t_vec3	*h;
	int	i;
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

			k = vec3_dotproduct(vec3_difference(intersect, o->ob_cones->cn_bottom, O_REPLACE), o->ob_cones->cn_vec_axis);

			if (k >= 0 && k <= o->ob_cones->cn_height)
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

// thanks for the website HEHEHHE
double	intersect_cone(t_ray *ray, t_object *o)
{
	double	values[3];
	double	coefficients[3];
	double	r;
	double	constant;
	t_vec3	*w;

	w = vec3_difference(ray->pos_vector, o->ob_coords, O_CREATE);
	r = o->ob_cones->cn_diameter / 2;
	constant = (r * r) / (o->ob_cones->cn_height * o->ob_cones->cn_height);

	double	dp1 = vec3_dotproduct(o->ob_cones->cn_vec_axis, ray->dir_vector);
	double	dp2 = vec3_dotproduct(o->ob_cones->cn_vec_axis, w);

	coefficients[0] = 1 - ((constant + 1) * (dp1 * dp1));
	coefficients[1] = vec3_dotproduct(w, ray->dir_vector) - ((constant + 1) * (dp1 * dp2));
	coefficients[2] = vec3_dotproduct(w, w) - ((constant + 1) * (dp2 * dp2));

	solve_quad_cn(coefficients, values);
	vec3_free(&w);
	if (values[0] < 0)
		return (ERROR);
	if (values[1] < 0 && values[2] < 0)
		return (ERROR);
	return (cn_test_intersect(ray, o, &values[1]));
}