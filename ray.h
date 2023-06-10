#ifndef __RAY_H__
#define __RAY_H__

#include "vector.h"


#define	LIGHT		0
#define	COLLIDED	1
#define SHADOW		2
typedef struct s_ray
{
	// ray type
	int			type;
	// position vector
	t_vector	*pos_vector;

	// direction vector
	t_vector	*dir_vector;

	// rgb
	t_vector	*color;

} t_ray;

t_ray	*init_ray(t_vector	*pos_vector, t_vector *dir_vector);
void	free_ray(t_ray **ray);
t_ray	*dup_ray(t_ray *source);

#endif