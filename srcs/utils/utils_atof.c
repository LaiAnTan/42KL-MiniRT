# include "../../headers/minirt.h"

float	ft_atof(char *str)
{
	int		dec;
	float	val;
	float	sign;

	dec = -1;
	sign = 1;
	val = 0;
	if (is_valid(str) == 0)
		return (NAN);
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	while (*str != '\0' && *str != '.')
	{
		if (*str >= '0' && *str <= '9')
			val = (val * 10) + (*str - '0');
		++str;
	}
	if (*str == '.')
		++str;
	while (*str != '\0' && *str != '.')
	{
		if (*str >= '0' && *str <= '9')
			val += (pow(10, dec) * (*str - '0'));
		dec--;
		++str;
	}
	return (val * sign);
}