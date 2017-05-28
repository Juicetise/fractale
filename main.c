#include "fractal.h"

int		ft_close(t_q *q)
{
	mlx_clear_window(q->mx, q->wn);
	mlx_destroy_window(q->mx, q->wn);
	free(q);
	exit(0);
}

int		mousexy(int x, int y, t_q *q)
{
	if (q->vit == 1)
	{
		q->jul_x = x * 0.05;
		q->jul_y = y * 0.05;
	}
	if (q->vit == -1)
	{
		q->jul_x = x * 0.01;
		q->jul_y = y * 0.01;
	}
	printf("%d\n", x);
	printf("%d\n", y);
	threaded_render(q);
	return (0);
}

void			calc_zoom(int x, int y, int sense, t_q *q)
{
	q->tmp_x = q->x1 + x * (q->x2 - q->x1) / 800;
	q->tmp_y = q->y1 + y * (q->y2 - q->y1) / 800;
	q->tmp_x2 = q->x1;
	q->tmp_y2 = q->y1;
	if (sense)
	{
		q->zoom *= 2;
		q->x1 = q->tmp_x - (q->x2 - q->x1) / 4;
		q->x2 = q->tmp_x + (q->x2 - q->tmp_x2) / 4;
		q->y1 = q->tmp_y - (q->y2 - q->y1) / 4;
		q->y2 = q->tmp_y + (q->y2 - q->tmp_y2) / 4;
	}
	else
	{
		q->zoom /= 2;
		q->x1 = q->tmp_x - (q->x2 - q->x1);
		q->x2 = q->tmp_x + (q->x2 - q->tmp_x2);
		q->y1 = q->tmp_y - (q->y2 - q->y1);
		q->y2 = q->tmp_y + (q->y2 - q->tmp_y2);
	}
}

int		mousezoom(int button, int x, int y, t_q *q)
{
	if (x > 0 && x < 800 && y > 0 && y < 800 && (button == 1 || button == 5))
		calc_zoom(x, y, 0, q);
	else if (x > 0 && x < 800 && y > 0 && y < 800 && (button == 2 || button == 4))
		calc_zoom(x, y, 1, q);
	threaded_render(q);
	return (0);
}

int		my_key_funct(int keycode, t_q *q)
{
	printf("%d\n", keycode);
	if (keycode == 126)
		q->ymove = q->ymove + 5;
	if (keycode == 125)
		q->ymove = q->ymove - 5;
	if (keycode == 124)
		q->xmove = q->xmove + 5;
	if (keycode == 123)
		q->xmove = q->xmove - 5;
	if (keycode == 8)
		q->vit = -q->vit;
	if (keycode == 3)
	{
		q->zoom = 140.000000;
		q->select = 1;
	}
	if (keycode == 4)
	{
		q->zoom = 140.000000;
		q->select = 3;
	}
	if (keycode == 5)
	{
		q->zoom = 300.000000;
		q->select = 2;
	}
	if (keycode == 9)
	{
		if (q->color == 0x00000FFF)
			q->color = 0x000000FF;
		else if (q->color == 0x000000FF)
			q->color = 0x00000000;
		else if (q->color == 0x00000000)
			q->color = 0x00000FFF;
	}
	if (keycode == 12)
		q->max_ite++;
	if (keycode == 13)
	{
		printf("%d\n", q->max_ite);
		q->max_ite--;
	}
	if (keycode == 53)
		ft_close(q);
	threaded_render(q);
	return (0);
}

int		getcolor(int i)
{
	int	color[49] = { 0x00FF0900, 0x00E8001E, 0x00FF0060, 0x00E80091, 0x00FF00DE, 0x00D900E8, 0x00CD00FF, 0x009B00E8, 0x008800FF, 0x005C00E8, 0x004300FF, 0x001E00E8, 0x000001FF, 0x00001FE8, 0x000043FF, 0x00005BE8, 0x000085FF, 0x000097E8, 0x0000C7FF, 0x0000D3E8, 0x0000FFF4, 0x0000E8BE, 0x0000FFAD, 0x0000E87D, 0x0000FF66, 0x0000E83C, 0x0000FF1F, 0x0005E800, 0x0032FF00, 0x0055E800, 0x008AFF00, 0x00A5E800, 0x00E1FF00,	0x00E8E400, 0x00FFEE00, 0x00E8CD00, 0x00FFD500, 0x00E8B700, 0x00FFBC00, 0x00E8A000, 0x00FFA300, 0x00E88900, 0x00FF8500, 0x00E86900, 0x00FF6100, 0x00E84800, 0x00FF3C00, 0x00E82600, 0x00FF1800 };
	while (i > 49)
		i = i - 49;
	return (color[i]);
		
}

int		julia(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = (x / q->zoom + q->x1) + (y / q->zoom + q->y1) * I;
	unth->c = 0.285 * q->jul_y + 0.01 * q->jul_x * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 8 && unth->i < q->max_ite)
	{
		unth->z = unth->z * unth->z + unth->c;
		unth->i++;
	}
	if (q->colortype == 1)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	}
	if (q->colortype == 2)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, getcolor(unth->i));
	}

	return (0);
}

int		newton(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = (x / q->zoom + q->x1) + (y / q->zoom + q->y1) * I;
	unth->c = -2 * q->jul_y - 2 * q->jul_x * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 8 && unth->i < q->max_ite)
	{
		unth->z = unth->z - (unth->z * unth->z * unth->z - unth->c) / (unth->z * unth->z * 3 * unth->c);
		unth->i++;
	}
	if (q->colortype == 1)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	}
	if (q->colortype == 2)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, getcolor(unth->i));
	}

	return (0);
}

int		newton2(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = (x / q->zoom + q->x1) + (y / q->zoom + q->y1) * I;
	unth->c = -2 * q->jul_y - 2 * q->jul_x * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 8 && unth->i < q->max_ite)
	{
		unth->z = (unth->z * unth->z * unth->z * unth->z + unth->c) / (unth->z * unth->z * unth->z);
		unth->i++;
	}
	if (q->colortype == 1)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	}
	if (q->colortype == 2)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, getcolor(unth->i));
	}
	return (0);
}


int		mandelbrot(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = 0;
	unth->c = ((x / q->zoom + q->x1) + (q->xmove / q->zoom)) + ((y  / q->zoom + q->y1) + (q->ymove / q->zoom)) * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 8 && unth->i < q->max_ite)
	{
		unth->z = unth->z * unth->z + unth->c;
		unth->i++;
	}
	if (q->colortype == 1)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	}
	if (q->colortype == 2)
	{
		if (unth->i == q->max_ite)
			pxl2img(q, x, y, BLACK);
		else
			pxl2img(q, x, y, getcolor(unth->i));
	}
	return (0);
}


void	pxl2img(t_q *q, int x, int y, int color)
{
	if (x > q->height || x < 0 || y > q->width || y < 0)
		return ;
	*(int *)&q->data[(y * q->len) + (x * (q->bpp / 8))] = color;
}



static void		draw_fractal(t_q *q, int part, t_th_fract *unth)
{
	register int		x;
	register int		y;
	int					stop;
	int					start;
	
	start = (q->height/ THREADS) * part;
	stop = (q->height / THREADS) * (part + 1);
	x = -400;
	y = start;
	while (y < stop)
	{
		while (x < q->height)
		{
			if (q->select == 1)
				julia(q, x, y, unth);
			else if (q->select == 2)
				mandelbrot(q, x, y, unth);
			else if (q->select == 3)
				newton(q, x, y, unth);
			x++;
		}
		x = 0;
		y++;
	}
}

static void		*threaderize_fractal(void *th)
{
	t_th_fract			*unth;
	
	unth = (t_th_fract *)th;
	draw_fractal(unth->q, unth->part, unth);
	pthread_exit(NULL);
}

int				threaded_render(t_q *q)
{
	pthread_t			tid[THREADS];
	t_th_fract			f_threads[THREADS];
	register int		i;
	
	i = 0;
	while (i < THREADS)
	{
		f_threads[i].q = q;
		f_threads[i].part = i;
		pthread_create(&tid[i], NULL, threaderize_fractal, &f_threads[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(tid[i++], NULL);
	mlx_put_image_to_window(q->mx, q->wn, q->img, 0, 0);
	return (0);
}

void	init(t_q *q)
{
	q->select = 2;
	q->height = 800;
	q->width = 800;
	q->zoom = 300;
	q->zoom_i = 10;
	q->max_ite = 25;
	q->g = 1;
	q->vit = 1;
	q->y = 0;
	q->y1 = -1.2;
	q->y2 = 1.2;
	q->x1 = -2.1;
	q->x2 = 0.6;
	q->xmove = 0;
	q->ymove = 0;
	q->colortype = 2;
	q->color = 0x000000FF;
	q->mx = mlx_init();
	q->wn = mlx_new_window(q->mx, q->height, q->width, "pdurand - FRACTAL");
	q->img = mlx_new_image(q->mx, q->height, q->width);
	q->data = mlx_get_data_addr(q->img, &q->bpp, &q->len, &q->endian);
}

int		main()
{
	t_q	*q;
	
	q = (t_q *)malloc(sizeof(t_q));
	init(q);
	mlx_hook(q->wn, 6, (1L << 6), *mousexy, q);
	mlx_hook(q->wn, 2, (1L << 0), my_key_funct, q);
	mlx_mouse_hook(q->wn, mousezoom, q);
	mlx_expose_hook(q->wn, threaded_render, q);
	mlx_loop(q->mx);
}
