# include "../../headers/minirt.h"

float	ft_atof(char *str)
{
	int		dec;
	float	val;
	float	sign;

	dec = -1;
	sign = 1;
	val = 0;
	if (is_decimal(str) == 0)
		return (0); // i dont like this but sure
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
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