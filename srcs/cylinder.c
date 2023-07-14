#include "../headers/minirt.h"

double	find_z_intersect(t_ray *r, t_object *o)
{
	// todo: sub into formula to find intersection point
}

t_vec3	*calc_cylinder_norm(t_ray *r, t_object *o)
{
	t_vec3	*norm;
	t_vec3	*coords;

	// normal of cylinder starts at the center of cylinder and ends at the intersection point
	// maintain same z height
	coords = vec3_dup(o->ob_coords);
	coords->raw_matrix->m[3][0] = find_z_intersect(r, o);

	norm = vec3_difference(r->pos_vector, coords);
	return (norm);
}

void	solve_quad_cy(double *coefficients, double *result)
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

// need a specific center bottom getter (since the cylinder axis isnt constantly 0,0,1)
t_vec3	*get_centre_bottom(t_object *o)
{
	double	diff;
	t_vec3	*ret;
	t_vec3	*to_min;

	diff = o->ob_cylinders->cy_height / 2;
	to_min = vec3_scalar_multi(o->ob_cylinders->cy_vec_axis, diff);
	ret = vec3_difference(o->ob_coords, to_min);
	return (ret);
}

double    intersect_cylinder(t_ray *ray, t_object *o)
{
    double	values[3];
    double	coefficients[3];

    t_vec3	*modified_ray_pos;
    t_vec3	*center_bottom;
    t_vec3	*w;

    modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords);
	center_bottom = get_centre_bottom(o);
    // center_bottom = vec3_dup(o->ob_coords);
    // center_bottom->raw_matrix->m[2][0] -= o->ob_cylinders->cy_height / 2;
    w = vec3_difference(modified_ray_pos, center_bottom);

    coefficients[0] = vec3_dotproduct(ray->dir_vector, ray->dir_vector) - 
                        (vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis));

    coefficients[1] = 2 * (vec3_dotproduct(ray->dir_vector, w) -
                        vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) *
                            vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis));

    coefficients[2] = vec3_dotproduct(w, w) - 
						(vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis) * vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis)) -
                        ((o->ob_cylinders->cy_diameter / 2) * (o->ob_cylinders->cy_diameter / 2));

    solve_quad_cy(coefficients, values);

    

    if (values[0] < 0)
        return (ERROR);
    if (values[1] < 0 && values[2] < 0)
        return (ERROR);

	// fun fact, we gotta test both values :P
    values[0] = fmin(values[1], values[2]);
    if (values[0] < 0)
        values[0] = fmax(values[1], values[2]);

	// calculate intersection point
	t_vec3	*intersection_point;
	
	intersection_point = vec3_addition(modified_ray_pos, vec3_scalar_multi(ray->dir_vector, values[0]));

	vec3_free(&modified_ray_pos);

	double z;
	t_vec3	*temp;
	t_vec3	*h;

	h = vec3_dup(o->ob_cylinders->cy_vec_axis);
	// mhm, weird shit
	// this should be the correct one (based on website), but it doesnt work...
	// oH well
	// h = vec3_scalar_multi(o->ob_cylinders->cy_vec_axis, o->ob_cylinders->cy_height);
	temp = vec3_difference(intersection_point, center_bottom);
	z = vec3_dotproduct(temp, h);

	vec3_free(&temp);
	vec3_free(&h);

	if (z <=0)
	{
		// test with base cap
		return (ERROR);
	}
	else if (z > o->ob_cylinders->cy_height) // this should be the height of the cylinder
	{
		//test with top cap
		return (ERROR);
	}
	else
		return (values[0]);
}