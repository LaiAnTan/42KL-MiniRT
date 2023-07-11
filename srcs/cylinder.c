#include "../headers/minirt.h"

// // returns a rotation matrix that transform whatever from is to (0,0,1);
// static t_matrix *construct_rotation(t_vec3 *from)
// {
// 	t_matrix	*rotation;
// 	matrix_type	straight_up_val[] = {0,0,1};
// 	t_vec3		*straight_up = vec3_init_from_array(straight_up_val);
// 	t_vec3		*fuck_me;

// 	rotation = m_init_empty(4, 4);

// 	t_vec3		*left_or_right_idk = vec3_crossproduct(from, straight_up);

// 	// z turn value ready
// 	t_vec3		*norm_left = vec3_normalize(left_or_right_idk);

// 	return (rotation);
// }


// x^2 + y^2 = r^2

// diameter
// height
// axis of cylinder (put it at (0,0,1) )

// theres the orientation matrix and the full transformation matrix
double	intersect_cylinder(t_ray *ray, t_object *o)
{
	t_vec3	*modified_ray_pos;
	t_vec3	*modified_ray_dir;

	modified_ray_pos = vec3_difference(ray->pos_vector, o->ob_coords);
	apply_matrix(&modified_ray_pos, o->ob_cylinders->cy_model_mtrx);

	modified_ray_dir = vec3_dup(ray->dir_vector);
	apply_matrix(&modified_ray_dir, o->ob_cylinders->cy_orient_mtrx);
}