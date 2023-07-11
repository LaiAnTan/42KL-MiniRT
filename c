# define CY_LENGTH 6

double    intersect_cylinder(t_ray *ray, t_object *o)
{
    double    values[3];
    double    coefficients[3];

    t_vec3    *modified_ray_pos;
    t_vec3    *center_bottom;
    t_vec3    *w;

    modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords);
    center_bottom = vec3_dup(o->ob_coords);
    center_bottom->raw_matrix->m[3][0] -= CY_LENGTH / 2;
    w = vec3_difference(modified_ray_pos, center_bottom);

    coefficients[0] = vec3_dotproduct(ray->dir_vector, ray->dir_vector) - 
                        vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis);

    coefficients[1] = 2 * (vec3_dotproduct(ray->dir_vector, w) -
                        vec3_dotproduct(ray->dir_vector, o->ob_cylinders->cy_vec_axis) *
                            vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis));

    coefficients[2] = vec3_dotproduct(w, w) - vec3_dotproduct(w, o->ob_cylinders->cy_vec_axis) -
                        ((o->ob_cylinders->cy_diameter / 2) * (o->ob_cylinders->cy_diameter / 2));

    solve_quad(coefficients, values);

    vec3_free(&modified_ray_pos);

    if (values[0] < 0)
        return (ERROR);
    if (values[1] < 0 && values[2] < 0)
        return (ERROR);

    values[0] = fmin(values[1], values[2]);
    if (values[0] < 0)
        values[0] = fmax(values[1], values[2]);

    return (values[0]);
}