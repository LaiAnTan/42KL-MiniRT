/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:51:31 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/04 23:39:41 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// unpacks a string of 3 values (255,255,255) into an array of integers (size 3)
// tokens is a 2d array (free_2d_array already checks if tokens is empty)
double	*unpack_3_int_values(char *values)
{
	int		i;
	double	*unpacked;
	char	**tokens;

	tokens = ft_split(values, ',');
	if (!tokens || count_2d_array(tokens) > 3)
	{
		free_2d_array(tokens);
		return (NULL);
	}
	i = -1;
	unpacked = (double *) malloc(sizeof(double) * 3);
	while (++i < 3)
	{
		if (is_digit(tokens[i]) == 0)
		{
			free_2d_array(tokens);
			free(unpacked);
			return (NULL);
		}
		unpacked[i] = ft_atoi(tokens[i]);
	}
	free_2d_array(tokens);
	return (unpacked);
}

// unpacks a string of 3 values (1.0,2.3,3.21) into an array of doubles (size 3)
// tokens is a 2d array (free_2d_array already checks if tokens is empty)
double	*unpack_3_double_values(char *values)
{
	int		i;
	double	*unpacked;
	char	**tokens;

	tokens = ft_split(values, ',');
	if (!tokens || count_2d_array(tokens) > 3)
	{
		free_2d_array(tokens);
		return (NULL);
	}
	unpacked = (double *) malloc(sizeof(double) * 3);
	i = -1;
	while (++i < 3)
	{
		if (is_valid(tokens[i]) == 0)
		{
			free_2d_array(tokens);
			free(unpacked);
			return (NULL);
		}
		unpacked[i] = (double) ft_atof(tokens[i]);
	}
	free_2d_array(tokens);
	return (unpacked);
}

static int	count_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			++count;
		++str;
	}
	return (count);
}

// checks if the string is a valid string of 3 values (255,255,255)
// values is a 2d array (leak)
int	is_valid_3_values(char *str)
{
	int		i;
	char	**values;

	if (count_char(str, ',') != 2)
		return (0);
	values = ft_split(str, ',');
	if (count_2d_array(values) != 3)
	{
		free_2d_array(values);
		return (0);
	}
	i = -1;
	while (values[++i])
	{
		if (is_digit(values[i]) == 0 && is_valid(values[i]) == 0)
		{
			free_2d_array(values);
			return (0);
		}
	}
	free_2d_array(values);
	return (1);
}
