# include "../headers/minirt.h"

void	raster_to_ndc(double *x, double *y)
{
	*x = (*x + 0.5) / WIDTH;
	*y = (*y + 0.5) / HEIGHT;
}

void	ndc_to_screen(double *x, double *y)
{
	*x = 2 * (*x) - 1;
	*y = 2 * (*y) - 1;
}

void	screen_to_view(double *x, double *y, double fov)
{
	double	aspect_ratio;

	aspect_ratio = WIDTH / HEIGHT;
	*x = (2 * (*x) - 1) * aspect_ratio * tan(fov / 2);
	*y = (1 - 2 * (*y)) * tan(fov / 2);
}

t_vec4	*convert_pixels(int pixel_y, int pixel_x, t_camera *camera)
{
	double	*x;
	double	*y;
	t_vec4	*center;

	x = (double *) malloc(sizeof(double));
	y = (double *) malloc(sizeof(double));
	*x = (double) pixel_x;
	*y = (double) pixel_y;
	raster_to_ndc(x, y);
	ndc_to_screen(x, y);
	screen_to_view(x, y, camera->cam_fov);

	center = vec4_init(*x, *y, -1.0f, 1.0f);
	return (center);
}

