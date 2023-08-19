#include "../headers/xpm_extractor.h"

// creates a image based on the xlm file given and returns it
// MAKE SURE FILENAME IS MALLOCED
t_texture	*texture_init(char *filename, void *mlx_ptr)
{
	t_texture	*ret;
	t_img_info	*temp;

	ret = malloc(sizeof(t_texture));
	ret->filename = filename;
	ret->data.img = mlx_xpm_file_to_image(mlx_ptr, filename, &ret->width, &ret->height);
	if (!ret->data.img)
	{
		printf("oopsie something went wrong :(\n");
		return NULL;
	}
	temp = &ret->data;
	temp->addr = mlx_get_data_addr(temp->img, &temp->bits_per_pixel, &temp->line_length, &temp->endian);
	return (ret);
}

// gets the rgb value of the texture at point x and y
unsigned int	get_xy_rgb(t_texture *txtr, int x, int y)
{
	t_img_info	*pntr;
	char		*dst;

	pntr = &txtr->data;
	dst = pntr->addr + (y * pntr->line_length + x * (pntr->bits_per_pixel / 8));
	return (*((unsigned *)dst));
}

// gets the rgb value on a point, returns in t_vec3 format
// uv is apparent in the fucking range of [-1, 1] im gonna kill someone
// so wee going to respect that
// reverted back to [0,1]
unsigned int get_rgb_ui(t_texture *txtr, double u, double v)
{
	unsigned int	rgb;
	int x;
	int y;

	// grab the rbg value of the respective uv coordinate
	// for range -1 to 1
	// x = round((txtr->width / 2) * (1 + u));
	// y = round((txtr->height / 2) * (1 + v));
	// printf("(%d, %d)\n", x, y);

	// for range 0 to 1
	x = round(txtr->width * u);
	y = round(txtr->height * v);
	rgb = get_xy_rgb(txtr, x, y);
	return (rgb);
}

// gets the rgb value on a point, returns in t_vec3 format
// uv LOOKS LIKE is in the range of [0,1]
// so wee going to respect that
// store array: 0, 1, 2 = r, g, b
t_vec3	*get_rgb(t_texture *txtr, double u, double v)
{
	unsigned int	rgb;
	matrix_type	store[3];

	// grab the rbg value of the respective uv coordinate
	rgb = get_rgb_ui(txtr, u, v);

	// we dont need to care about transparancy (i fucking hope)
	store[0] = (matrix_type) (int) ((rgb >> 16) & 0xFF);
	store[1] = (matrix_type) (int) ((rgb >> 8) & 0xFF);
	store[2] = (matrix_type) (int) (rgb & 0xFF);
	return (vec3_init_from_array(store));
}

void	free_texture(t_texture *a, void *mlx)
{
	if (!a)
		return ;
	free(a->filename);
	mlx_destroy_image(mlx, a->data.img);
	free(a);
}