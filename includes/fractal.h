/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 17:28:25 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/04 17:28:27 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <mlx.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>
# include <stdio.h>
# include <pthread.h>

# define RED 0x00E74C3C
# define BLUE 0x005DADE2
# define GREEN 0x002ECC71
# define YELLOW 0x00F1C40F
# define GREY 0x00BDC3C7
# define BROWN 0x00D35400
# define PURPLE 0x009B59B6
# define WHITE 0x00F7F9F9
# define ORANGE 0x00F39C12
# define BLACK 0x00000000
# define THREADS 8

typedef _Complex double		t_complex;

typedef struct		s_q
{
	int				height;
	int				width;
	void			*mx;
	void			*wn;
	void			*img;
	int				color;
	char			*argv;
	int				bpp;
	int				len;
	int				endian;
	char			*data;
	t_complex		z;
	t_complex		c;
	int				i;
	double			zoom;
	double			zoom_i;
	int				max_ite;
	int				select;
	double			jul_x;
	double			jul_y;
	int				speed;
	double			xmove;
	double			ymove;
	int				xdist;
	int				ydist;
	double			x1;
	double			x2;
	double			y1;
	double			y2;
	double			tmp_x;
	double			tmp_y;
	double			tmp_x2;
	double			tmp_y2;
	int				colortype;
	int				fracolorize;
	int				stuck;
	int				error;
	int				start;
	int				stop;
	int				x;
	int				y;
	int				colortab[49];
}					t_q;

typedef struct		s_th_fract
{
	double			i;
	t_complex		z;
	t_complex		c;
	t_q				*q;
	int				part;
}					t_th_fract;

void				calc_zoom(int x, int y, int sense, t_q *q);
int					threaded_render(t_q *q);
int					newton(t_q *q, int x, int y, t_th_fract *unth);
int					julia(t_q *q, int x, int y, t_th_fract *unth);
int					mandelbrot(t_q *q, int x, int y, t_th_fract *unth);
int					newton2(t_q *q, int x, int y, t_th_fract *unth);
void				pxl2img(t_q *q, int x, int y, int color);
int					clear_image(t_q *q, int x, int y);
void				init(t_q *q);
int					fractal_it(t_q *q, int x, int y);
int					my_key_funct(int keycode, t_q *q);
int					ft_close(t_q *q);
void				error(int n);
int					julia(t_q *q, int x, int y, t_th_fract *unth);
int					newton(t_q *q, int x, int y, t_th_fract *unth);
int					flower(t_q *q, int x, int y, t_th_fract *unth);
int					mandelbrot(t_q *q, int x, int y, t_th_fract *unth);
void				init(t_q *q);
int					param_parse(char *str, t_q *q);
int					getcolor(int i, t_q *q);
int					ft_strcmp(const char *s1, const char *s2);
int					mousezoom(int button, int x, int y, t_q *q);
void				calc_zoom(int x, int y, int sense, t_q *q);
int					mousexy(int x, int y, t_q *q);
void				init_julia(t_q *q);
void				init_mandelbrot(t_q *q);
void				init_newton(t_q *q);
void				init_flower(t_q *q);
void				draw_selection(t_q *q, int x, int y, t_th_fract *unth);
void				populatecolortab(t_q *q);
void				populatecolortab2(t_q *q);
void				my_key_funct2(int keycode, t_q *q);
void				my_key_funct3(int keycode, t_q *q);

#endif
