/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:07:30 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:07:32 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

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
			pxl2img(q, x, y, getcolor(unth->i, q));
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
			pxl2img(q, x, y, getcolor(unth->i, q));
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
		unth->z = (unth->z * unth->z * unth->z * unth->z * unth->z + unth->c) / (unth->z * unth->z * unth->z);
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
			pxl2img(q, x, y, getcolor(unth->i, q));
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
			pxl2img(q, x, y, getcolor(unth->i, q));
	}
	return (0);
}

