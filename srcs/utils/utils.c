/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:19:47 by tlai-an           #+#    #+#             */
/*   Updated: 2022/11/16 18:23:52 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minirt.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_append(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s1 != NULL)
	{
		while (s1[j] != '\0')
			temp[i++] = s1[j++];
	}
	if (s2 != NULL)
	{
		while (*s2 != '\0')
			temp[i++] = *s2++;
	}
	temp[i] = '\0';
	free(s1);
	return (temp);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	dest = (char *) malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	free(str);
	return (dest);
}

void	copy_int_arr(int *copy_from, int *copy_to, int size) // both arrays must have the same size
{
	int		i;

	i = 0;
	while (i < size)
	{
		copy_to[i] = copy_from[i];
		++i;
	}
	return ;
}

void	copy_double_arr(double *copy_from, double *copy_to, int size) // both arrays must have the same size
{
	int		i;

	i = 0;
	while (i < size)
	{
		copy_to[i] = copy_from[i];
		++i;
	}
	return ;
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (!(!s1 && !s2));
	while ((s1[i] == s2[i]))
	{
		if (s1[i] == '\0')
			return (0);
		++i;
	}
	return (s1[i] - s2[i]);
}

char	*ft_substr(char *s, unsigned int start, unsigned int end)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!s && start > end)
		return (0);
	if (end >= (unsigned int) ft_strlen(s))
		end = ft_strlen(s);
	if (start >= (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	str = (char *) malloc(sizeof(char) * ((end - start) + 2));
	if (str == 0)
		return (0);
	while (start <= end && s[start] != '\0')
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	count_2d_array(char **e)
{
	int	i;

	i = 0;
	while (e[i])
		++i;
	return (i);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	rtval;

	sign = 1;
	rtval = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (rtval >= 214748364 && *str > '7' && sign == 1)
			return (-1);
		if (rtval >= 214748364 && *str > '8' && sign == -1)
			return (0);
		rtval = (rtval * 10) + (*str - '0');
		str++;
	}
	return ((int)(rtval * sign));
}

int		is_digit(char *str)
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

int		is_decimal(char *str)
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
