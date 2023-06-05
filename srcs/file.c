# include "../headers/minirt.h"

t_scene	*file_create_scene(char *filename)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	
}