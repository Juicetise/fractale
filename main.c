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
	if (keycode == 3)
	{
		q->zoom = 240.000000;
		q->select = 1;
	}
	if (keycode == 4)
	{
		q->zoom = 240.000000;
		q->max_ite = 20;
		q->select = 3;
	}
	if (keycode == 5)
	{
		q->zoom = 370.000000;
		q->select = 2;
	}
	if (keycode == 9)
	{
		if (q->color == 0x00000FFF)
			q->color = 0x000000FF;
		else if (q->color == 0x000000FF)
			q->color = 0x00000FFF;
	}
	if (keycode == 12)
		q->max_ite++;
	if (keycode == 13)
	{
		printf("%d\n", q->max_ite);
		q->max_ite--;
	}
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
		pxl2img(q, x, y, (q->color << 14) + q->i * 500);
	return (0);
}

int		newton2(t_q *q, int x, int y)
{
	q->i = 0;
	q->z = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	q->c = -2 - 2 * I;
	while (creal(q->z) * creal(q->z) + cimag(q->z) * cimag(q->z) < 16 && q->i < q->max_ite)
	{
		q->z = q->z - (q->z * q->z * q->z - q->c) / (q->z * q->z * 3 * q->c);
		q->i++;
	}
	if (q->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (q->color << 14) + q->i * 500);
	return (0);
}

int		newton(t_q *q, int x, int y)
{
	q->i = 0;
	q->z = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	q->c = -2 - 2 * I;
	while (creal(q->z) * creal(q->z) + cimag(q->z) * cimag(q->z) < 16 && q->i < q->max_ite)
	{
		q->z = (q->z * q->z * q->z * q->z + q->c) / (q->z * q->z * q->z);
		q->i++;
	}
	if (q->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (q->color << 14) + q->i * 500);
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
		pxl2img(q, x, y, (q->color << 14) + q->i * 500);
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
			if (q->select == 3)
				newton(q, x, y);
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
	q->zoom = 370;
	q->max_ite = 100;
	q->g = 1;
	q->color = 0x000000FF;
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
