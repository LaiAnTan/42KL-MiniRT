#include "../headers/minirt.h"

int main(int argc, char **argv)
{
	t_data		*data;
	int			loop;

	if (argc != 2)
		return (ERROR);
	data = (t_data *) malloc(sizeof(t_data));
	data->mlx = (t_mlx_info *) malloc(sizeof(t_mlx_info));
	data->scene = file_create_scene(argv[1]);
	scene_print_stats(data->scene);
	data->mlx->mlx = mlx_init();
	data->mlx->mlx_win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, argv[1]);
	data->mlx->img.img = NULL;
	loop = 0;
	while (1)
	{
		get_image(&data->mlx->img, data->mlx->mlx);
		raytrace(data->scene, data->mlx);
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img.img, 0, 0);
		clean_loop(data->mlx);
		loop += 10;
		if (loop > WIDTH)
			loop = -1 * WIDTH;
	}
	mlx_loop(data->mlx->mlx);
	scene_free_objects(data->scene);
}

// test view matrices
// delete once done

// int main(void)
// {
// 	t_cylinder cy;

// 	cy.cy_coords = vec4_init(-50, 0, 20, 1);
// 	cy.cy_vec_axis = vec4_init(0, 1, 0, 1);

// 	printf("cylinder coords\n");
// 	vec4_print(cy.cy_coords);
// 	printf("cylinder axis vector\n");
// 	vec4_print(cy.cy_vec_axis);

// 	t_matrix *model_matrix = get_model_matrix(&cy);
// 	printf("model_matrix = \n");
// 	m_print_matrix(model_matrix);
// 	t_matrix *inv_model_matrix = get_inverse_transform(model_matrix);
// 	printf("inverse model matrix = \n");
// 	m_print_matrix(inv_model_matrix);

// }
