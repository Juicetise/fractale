/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:07:10 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:07:12 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

int		my_key_funct(int keycode, t_q *q)
{
	if (keycode > 0 && keycode < 14)
		my_key_funct2(keycode, q);
	if (keycode == 49 || keycode == 119)
		my_key_funct3(keycode, q);
	if (keycode == 69)
		q->fracolorize = q->fracolorize + 100;
	if (keycode == 78)
		q->fracolorize = q->fracolorize - 100;
	if (keycode == 126)
		q->ymove = q->ymove + 5;
	if (keycode == 125)
		q->ymove = q->ymove - 5;
	if (keycode == 124)
		q->xmove = q->xmove + 5;
	if (keycode == 123)
		q->xmove = q->xmove - 5;
	if (keycode == 53)
		ft_close(q);
	threaded_render(q);
	return (0);
}

void	my_key_funct2(int keycode, t_q *q)
{
	if (keycode == 8)
		q->speed = -q->speed;
	if (keycode == 3)
		init_julia(q);
	if (keycode == 4)
		init_newton(q);
	if (keycode == 5)
		init_mandelbrot(q);
	if (keycode == 2)
		init_flower(q);
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
		q->max_ite--;
	return ;
}

void	my_key_funct3(int keycode, t_q *q)
{
	if (keycode == 49)
	{
		if (q->colortype == 1)
			q->colortype = 2;
		else if (q->colortype == 2)
			q->colortype = 1;
	}
	if (keycode == 119)
	{
		if (q->stuck == 0)
			q->stuck = 1;
		else if (q->stuck == 1)
			q->stuck = 0;
	}
	return ;
}
