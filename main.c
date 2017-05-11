#include "fractal.h"

int		ft_close(t_q *q)
{
	mlx_clear_window(q->mx, q->wn);
	mlx_destroy_window(q->mx, q->wn);
	free(q);
	exit(0);
}
int		my_key_funct(int keycode, t_q *q)
{
	printf("%d\n", keycode);
	if (keycode == 5)
	{
		if (q->select == 2)
			q->select = 1;
		else if (q->select == 1)
			q->select = 2;
	}
	if (keycode == 12)
		q->max_ite++;
	if (keycode == 13)
		q->max_ite--;
	if (keycode == 31)
		q->zoom = q->zoom + 10;
	if (keycode == 35)
		q->zoom = q->zoom - 10;
	if (keycode == 53)
		ft_close(q);
	expose_fdf(q);
	return (0);
}

int		julia(t_q *q, int x, int y)
{
	q->i = 0;
	q->z = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	q->c = 0.285 + 0.01 * I;
	while (creal(q->z) * creal(q->z) + cimag(q->z) * cimag(q->z) < 16 && q->i < q->max_ite)
	{
		q->z = q->z * q->z + q->c;
		q->i++;
	}
	if (q->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (START_COLOR << 14) + q->i * 500);
	/*if (q->i == q->max_ite)
		pxl2img(q, x, y, WHITE);
	else if (q->i == q->max_ite / 2)
		pxl2img(q, x, y, RED);
	else if (q->i == q->max_ite / 4)
		pxl2img(q, x, y, BLUE);
	else if (q->i == q->max_ite / 6)
		pxl2img(q, x, y, GREEN);
	else if (q->i == q->max_ite / 8)
		pxl2img(q, x, y, YELLOW);
	else if (q->i == q->max_ite / 3)
		pxl2img(q, x, y, GREY);
	else if (q->i == q->max_ite / 5)
		pxl2img(q, x, y, BROWN);
	else if (q->i == q->max_ite / 7)
		pxl2img(q, x, y, PURPLE);
	else if (q->i == q->max_ite / 9)
		pxl2img(q, x, y, ORANGE);
	else
		pxl2img(q, x, y, BLACK);*/
	return (0);
}

int		mandelbrot(t_q *q, int x, int y)
{
	
	q->i = 0;
	q->z = 0;
	q->c = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	while (creal(q->z) * creal(q->z) + cimag(q->z) * cimag(q->z) < 16 && q->i < q->max_ite)
	{
		q->z = q->z * q->z + q->c;
		q->i++;
	}
	if (q->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (START_COLOR << 14) + q->i * 500);
	/*if (q->i == q->max_ite)
		pxl2img(q, x, y, WHITE);
	else if (q->i == q->max_ite / 2)
		pxl2img(q, x, y, RED);
	else if (q->i == q->max_ite / 4)
		pxl2img(q, x, y, BLUE);
	else if (q->i == q->max_ite / 6)
		pxl2img(q, x, y, GREEN);
	else if (q->i == q->max_ite / 8)
		pxl2img(q, x, y, YELLOW);
	else if (q->i == q->max_ite / 3)
		pxl2img(q, x, y, GREY);
	else if (q->i == q->max_ite / 5)
		pxl2img(q, x, y, BROWN);
	else if (q->i == q->max_ite / 7)
		pxl2img(q, x, y, PURPLE);
	else if (q->i == q->max_ite / 9)
		pxl2img(q, x, y, ORANGE);
	else
		pxl2img(q, x, y, BLACK);*/
	return (0);
}

void	fractal(t_q *q)
{
	int x;
	int y;

	x = 0;
	y = 0;
	
	while (x < q->height)
	{
		while (y < q->width)
		{
			if (q->select == 1)
				julia(q, x, y);
			if (q->select == 2)
				mandelbrot(q, x, y);
			y++;
		}
		y = 0;
		x++;
	}
}

void	pxl2img(t_q *q, int x, int y, int color)
{
	if (x > q->height || x < 0 || y > q->width || y < 0)
		return ;
	*(int *)&q->data[(y * q->len) + (x * (q->bpp / 8))] = color;
}

int		expose_fdf(t_q *q)
{
	clear_image(q, 0, 0);
	fractal(q);
	mlx_put_image_to_window(q->mx, q->wn, q->img, 0, 0);
	return (0);
}

int		clear_image(t_q *q, int x, int y)
{
	while (y < q->width)
	{
		x = 0;
		while (x < q->height)
			pxl2img(q, x++, y, 0x00000000);
		y++;
	}
	return (0);
}

void	init(t_q *q)
{
	q->select = 2;
	q->height = 1000;
	q->width = 1000;
	q->zoom = 100;
	q->max_ite = 100;
	q->g = 1;
	q->mx = mlx_init();
	q->wn = mlx_new_window(q->mx, q->height, q->width, "pdurand - FDF");
	q->img = mlx_new_image(q->mx, q->height, q->width);
	q->data = mlx_get_data_addr(q->img, &q->bpp, &q->len, &q->endian);
}

int		main()
{
	t_q	*q;
	
	q = (t_q *)malloc(sizeof(t_q));
	init(q);
	mlx_hook(q->wn, 2, (1L << 0), my_key_funct, q);
	mlx_expose_hook(q->wn, expose_fdf, q);
	mlx_loop(q->mx);
}
