# include "../../headers/minirt.h"

// WHY IS THERE NO ABS FOR DOUBLE WTF
double	absolute(double val)
{
	if (val < 0)
		return (-1 * val);
	else
		return (val);
}

double	to_radian(double degree)
{
	return (degree * PI / 180);
}

double	to_degree(double rad)
{
	return (rad * 180 / PI);
}

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
