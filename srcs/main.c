#include "../headers/minirt.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		return (0);
	scene = file_create_scene(argv[1]);
	(void *) scene;
	return (0);
}