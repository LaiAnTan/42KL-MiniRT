# include "../../headers/minirt.h"

int		is_float(char *str)
{
	int	before_point;
	int	after_point;

	before_point = 0;
	after_point = 0;
	if (*str == '-' || *str == '+')
		++str;
	while ((*str != '\0' && *str != '.') && (*str >= '0' && *str <= '9'))
	{
		before_point += 1;
		++str;
	}
	++str;
	while ((*str != '\0') && (*str >= '0' && *str <= '9'))
	{
		after_point += 1;
		++str;
	}
	if (before_point <= 0 && after_point <= 0)
		return (0);
	return (1);
}

float	ft_atof(char *str)
{
	int		dec;
	float	val;
	float	sign;

	dec = -1;
	sign = 1;
	val = 0;
	if (is_float(str) == 0)
		return (0);
	if (*str == '-')
		sign = -1;
	while ((*str != '.' && *str != '\0') && (*str >= '0' && *str <= '9'))
	{
		val = (val * 10) + (*str - '0');
		++str;
	}
	++str;
	while ((*str != '\0') && *str >= '0' && *str <= '9')
	{
		val += (pow(10, dec) * (*str - '0'));
		++str;
		--dec;
	}
	return (val * sign);
}