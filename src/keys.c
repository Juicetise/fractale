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
	printf("%d\n", keycode);
	if (keycode == 119)
	{
		if (q->move == 0)
			q->move = 1;
		else if (q->move == 1)
			q->move = 0;
		printf("%d", q->move);
	}
	if (keycode == 49)
	{
		if (q->colortype == 1)
			q->colortype = 2;
		else if (q->colortype == 2)
			q->colortype = 1;
	}
	if (keycode == 69)
		q->frac = q->frac + 100;
	if (keycode == 78)
		q->frac = q->frac - 100;
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
		q->select= 1;
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
	if (keycode == 2)
		q->select = 4;
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
