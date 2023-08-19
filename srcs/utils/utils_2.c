/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:54 by tlai-an           #+#    #+#             */
/*   Updated: 2023/08/19 22:34:25 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

// WHY IS THERE NO ABS FOR DOUBLE WTF
double	abs_double(double val)
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

int	is_digit(char *str)
{
	if (*str == '-' || *str == '+')
		++str;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		++str;
	}
	return (1);
}
