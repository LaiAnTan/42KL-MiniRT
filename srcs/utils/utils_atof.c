/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:57 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 12:01:57 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

int	is_valid(char *str)
{
	int	point_num;
	int	digits;

	point_num = 0;
	digits = 0;
	if (*str == '+' || *str == '-')
		++str;
	while (*str != '\0')
	{
		if (*str == '.')
			++point_num;
		else if (*str >= '0' && *str <= '9')
			++digits;
		else
			return (0);
		++str;
	}
	if (point_num > 1 || !digits)
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
	if (is_valid(str) == 0)
		return (NAN);
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	while (*str != '\0' && *str != '.')
		val = (val * 10) + (*(str++) - '0');
	if (*str == '.')
		++str;
	while (*str != '\0' && *str != '.')
		val += (pow(10, dec--) * (*(str++) - '0'));
	return (val * sign);
}
