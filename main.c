#include "fractal.h"

int		ft_close(t_q *q)
{
	mlx_clear_window(q->mx, q->wn);
	mlx_destroy_window(q->mx, q->wn);
	free(q);
	exit(0);
}

void	mousexy(int x, int y, t_q *q)
{
	
}

void	mousezoom(int button, int x, int y, t_q *q)
int		my_key_funct(int keycode, t_q *q)
{
	printf("%d\n", keycode);
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
	threaded_render(q);
	return (0);
}

int		julia(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	unth->c = 0.285 + 0.01 * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 16 && unth->i < q->max_ite)
	{
		unth->z = unth->z * unth->z + unth->c;
		unth->i++;
	}
	if (unth->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	return (0);
}

int		newton2(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	unth->c = -2 - 2 * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 16 && unth->i < q->max_ite)
	{
		unth->z = unth->z - (unth->z * unth->z * unth->z - unth->c) / (unth->z * unth->z * 3 * unth->c);
		unth->i++;
	}
	if (unth->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	return (0);
}

int		newton(t_q *q, int x, int y, t_th_fract *unth)
{
	unth->i = 0;
	unth->z = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	unth->c = -2 - 2 * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 16 && unth->i < q->max_ite)
	{
		unth->z = (unth->z * unth->z * unth->z * unth->z + unth->c) / (unth->z * unth->z * unth->z);
		unth->i++;
	}
	if (unth->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
	return (0);
}


int		mandelbrot(t_q *q, int x, int y, t_th_fract *unth)
{
	
	unth->i = 0;
	unth->z = 0;
	unth->c = (x / q->zoom + x1) + (y / q->zoom + y1) * I;
	while (creal(unth->z) * creal(unth->z) + cimag(unth->z) * cimag(unth->z) < 16 && unth->i < q->max_ite)
	{
		unth->z = unth->z * unth->z + unth->c;
		unth->i++;
	}
	if (unth->i == q->max_ite)
		pxl2img(q, x, y, BLACK);
	else
		pxl2img(q, x, y, (q->color << 14) + unth->i * 500);
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
	x = 0;
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
	q->max_ite = 25;
	q->g = 1;
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
	mlx_hook(q->wn, 2, (1L << 0), my_key_funct, q);
	mlx_hook(q->wn, 6, (1L << 6), mousexy, q);
	mlx_mouse_hook(a->mlx->win, mousezoom, q);
	mlx_expose_hook(q->wn, threaded_render, q);
	mlx_loop(q->mx);
}
