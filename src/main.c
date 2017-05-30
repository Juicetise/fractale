/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:14:10 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:14:12 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

int		ft_close(t_q *q)
{
	mlx_clear_window(q->mx, q->wn);
	mlx_destroy_window(q->mx, q->wn);
	free(q);
	exit(0);
}

int		param_parse(char *str, t_q *q)
{
	if (ft_strcmp(str, "Mandelbrot") == 0)
		q->select = 2;
	else if (ft_strcmp(str, "Julia") == 0)
		q->select = 1;
	else if (ft_strcmp(str, "Newton") == 0)
		q->select = 3;
	else if (ft_strcmp(str, "Flower") == 0)
		q->select = 4;
	else
	{
		error(2);
		return(0);
	}
	return (1);
}

void	error(int n)
{
	if (n == 2)
		write(1, "Usage : ./fractol <fractal_name> : Mandelbrot | Julia | Newton | Flower\n", 72);
	return	;
}


int		main(int argc, char **argv)
{
	t_q	*q;
	
	q = NULL;
	if (argc != 2)
	{
		error(2);
		return (0);
	}
	if (argc == 2)
	{
		q = (t_q *)malloc(sizeof(t_q));
		if (param_parse(argv[1], q) == 0)
			return (0);
		init(q);
		mlx_hook(q->wn, 6, (1L << 6), *mousexy, q);
		mlx_hook(q->wn, 2, (1L << 0), my_key_funct, q);
		mlx_mouse_hook(q->wn, mousezoom, q);
		mlx_expose_hook(q->wn, threaded_render, q);
		mlx_loop(q->mx);
	}
}
