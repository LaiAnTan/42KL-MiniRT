/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:22 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/03 00:11:57 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

int	parse_line(t_scene *scene, char *line)
{
	int		error;
	char	**tokens;

	error = 0;
	tokens = ft_split(line, ' ');
	if (ft_strcmp("A", tokens[0]) == 0)
		error = handle_object_ambient(scene, tokens);
	else if (ft_strcmp("C", tokens[0]) == 0)
		error = handle_object_camera(scene, tokens);
	else if (ft_strcmp("L", tokens[0]) == 0)
		error = handle_object_light(scene, tokens);
	else if (ft_strcmp("sp", tokens[0]) == 0)
		error = handle_object_sphere(scene, tokens);
	else if (ft_strcmp("pl", tokens[0]) == 0)
		error = handle_object_plane(scene, tokens);
	else if (ft_strcmp("cy", tokens[0]) == 0)
		error = handle_object_cylinder(scene, tokens);
	else if (ft_strcmp("cn", tokens[0]) == 0)
		error = handle_object_cone(scene, tokens);
	free_2d_array(tokens);
	if (error)
		return (error);
	return (0);
}

// the bracket is necessary apparently
void	strip_nl(char **str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	if ((*str)[len - 1] != '\n')
		return ;
	new_str = (char *) malloc (sizeof(char) * ft_strlen(*str));
	while (i < len - 1)
	{
		new_str[i] = (*str)[i];
		++i;
	}
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
}

t_scene	*file_create_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	*new_scene;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	new_scene = scene_init();
	while (1)
	{
		line = get_next_line(fd);
		strip_nl(&line);
		if (!line)
			break ;
		if (parse_line(new_scene, line))
		{
			printf("Error in file configuration at line = %s\n", line);
			scene_free(new_scene, NULL);
			exit(0);
		}
		free(line);
	}
	if (!new_scene->sc_ambients)
		new_scene->sc_ambients = scene_new_ambient(NULL, 0);
	return (new_scene);
}
