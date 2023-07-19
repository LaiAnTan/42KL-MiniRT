# include "../headers/minirt.h"

/*               No switches?
** ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝
** ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇
** ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀
** ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀
** ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀
** ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀
** ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
** ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
*/

typedef	double (*object_runner) (t_ray *, t_object *);

// future me -> throw this into the minirt structure
double		object_switcher(int	value, t_ray *ray, t_object *o)
{
	object_runner	func_switch[4];
	func_switch[0] = intersect_circle;
	func_switch[1] = intersect_plane;
	func_switch[2] = intersect_cylinder;
	func_switch[3] = intersect_cone;

	return (func_switch[o->ob_type](ray, o));
}

t_object	*get_closest_object(t_ray *ray, t_scene *scene, int closest,
		double	*k_val)
{
	t_object	*cur;
	t_object	*closest_object_src;
	double		closest_object;
	double		r_to_o;

	cur = scene->sc_objs;
	closest_object = INFINITY;
	closest_object_src = NULL;
	while (cur)
	{
		r_to_o = object_switcher(cur->ob_type, ray, cur);

		// means collided d
		if (r_to_o != ERROR)
		{
			if (!closest)
			{
				*k_val = r_to_o;
				return (cur);
			}
			if (r_to_o < closest_object)
			{
				closest_object = r_to_o;
				closest_object_src = cur;
			}
		}
		cur = cur->next;
	}
	*k_val = closest_object;
	return (closest_object_src);
}

int	get_closest_light(t_ray *r, t_light *l, t_scene *scene)
{
	double		save;
	double		exceed_k;
	double		precision = 0.1f;
	t_vec3		*r_to_l;
	t_ray		*to_light;
	t_object	*collided_obj;

	r_to_l = vec3_difference(l->l_coords, r->pos_vector, O_CREATE);
	to_light = init_ray(vec3_dup(r->pos_vector), vec3_normalize(r_to_l, O_CREATE));
	exceed_k = vec3_magnitude_sqrd(r_to_l);

	move_ray(to_light, precision);

	collided_obj = get_closest_object(to_light, scene, 0, &save);
	free_ray(&to_light);

	if (collided_obj == NULL)
		return (SUCCESS);
	else
	{
		if ((save * save) > exceed_k)
			return (SUCCESS);
		else
			return (ERROR);
	}
}
