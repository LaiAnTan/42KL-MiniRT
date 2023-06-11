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

	// color of ray
	t_vec3		rgb[3];

} t_ray;

t_ray	*init_ray(t_vec4 *pos_vector, t_vec4 *dir_vector);
void	free_ray(t_ray **ray);
t_ray	*dup_ray(t_ray *source);

#endif