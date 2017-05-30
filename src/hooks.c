/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:06:48 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:06:51 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

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
			else if (q->select == 4)
				newton2(q, x, y, unth);
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
	
	mlx_clear_window(q->mx, q->wn);
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
