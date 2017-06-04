/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:11:57 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:11:59 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

void	init(t_q *q)
{
	populatecolortab(q);
	q->height = 800;
	q->width = 800;
	q->max_ite = 50;
	q->speed = 1;
	q->fracolorize = 0;
	q->colortype = 2;
	q->color = 0x000000FF;
	q->stuck = 1;
	q->mx = mlx_init();
	q->wn = mlx_new_window(q->mx, q->height, q->width, "pdurand - FRACTAL");
	q->img = mlx_new_image(q->mx, q->height, q->width);
	q->data = mlx_get_data_addr(q->img, &q->bpp, &q->len, &q->endian);
}

void	init_julia(t_q *q)
{
	q->select = 1;
	q->zoom = 190;
	q->xmove = -170;
	q->ymove = -170;
	q->y1 = -1.2;
	q->x1 = -1.2;
	q->x2 = 1.2;
	q->y2 = 1.2;
}

void	init_mandelbrot(t_q *q)
{
	q->select = 2;
	q->zoom = 300;
	q->xmove = 20;
	q->ymove = -40;
	q->y1 = -1.2;
	q->x1 = -2.1;
	q->x2 = 0.6;
	q->y2 = 1.2;
}

void	init_newton(t_q *q)
{
	q->select = 3;
	q->zoom = 140;
	q->xmove = -105;
	q->ymove = -105;
	q->y1 = -2.1;
	q->x1 = -2.1;
	q->x2 = 2.1;
	q->y2 = 2.1;
}

void	init_flower(t_q *q)
{
	q->select = 4;
	q->zoom = 210;
	q->xmove = -150;
	q->ymove = -150;
	q->y1 = -1.2;
	q->x1 = -1.2;
	q->x2 = 1.2;
	q->y2 = 1.2;
}
