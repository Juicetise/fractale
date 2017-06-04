/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:07:20 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:07:22 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

int		mousezoom(int button, int x, int y, t_q *q)
{
	if (x > 0 && x < 800 && y > 0 && y < 800 && (button == 2 || button == 5))
		calc_zoom(x, y, 0, q);
	else if (x > 0 && x < 800 && y > 0 && y < 800 &&
			(button == 1 || button == 4))
		calc_zoom(x, y, 1, q);
	threaded_render(q);
	return (0);
}

void	calc_zoom(int x, int y, int sense, t_q *q)
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

int		mousexy(int x, int y, t_q *q)
{
	if (x >= 0 && x <= 800 && y >= 0 && y <= 800 && q->stuck == 1)
	{
		x = x - 400;
		y = y - 400;
		if (q->speed == 1)
		{
			q->jul_x = x * 0.2;
			q->jul_y = y * 0.05;
		}
		if (q->speed == -1)
		{
			q->jul_x = x * 0.05;
			q->jul_y = y * 0.01;
		}
		threaded_render(q);
	}
	return (0);
}
