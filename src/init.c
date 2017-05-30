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
	q->frac = 0;
	q->xmove = 0;
	q->ymove = 0;
	q->colortype = 2;
	q->color = 0x000000FF;
	q->move = 1;
	q->mx = mlx_init();
	q->wn = mlx_new_window(q->mx, q->height, q->width, "pdurand - FRACTAL");
	q->img = mlx_new_image(q->mx, q->height, q->width);
	q->data = mlx_get_data_addr(q->img, &q->bpp, &q->len, &q->endian);
}

