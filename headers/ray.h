#ifndef __RAY_H__
#define __RAY_H__

# include "vec3.h"
# include "vec4.h"

/* Ray Types */
#define	LIGHT		0
#define	COLLIDED	1
#define SHADOW		2

typedef struct s_ray
{
	// ray type
	int			type;
	// position vector
	t_vec4	*pos_vector;

	// direction vector
	t_vec4	*dir_vector;

	// rgb
	t_vec3	*color;
	t_vec3	*a_color; // ambient
	t_vec3	*d_color; // diffuse
	t_vec3	*s_color; // specular

} t_ray;

t_ray	*init_ray(t_vec4 *pos_vector, t_vec4 *dir_vector);
void	free_ray(t_ray **ray);
t_ray	*dup_ray(t_ray *source);

#endif