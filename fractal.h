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
# define x1 -2.1
# define x2 0.6
# define y1 -1.2
# define y2 1.2

typedef _Complex double		t_complex;

typedef struct		s_q
{
	int				height;
	int				width;
	void			*mx;
	void			*wn;
	void			*img;
	int				color;
	int				x_ratio;
	int				y_ratio;
	char			*argv;
	int				bpp;
	int				len;
	int				endian;
	char			*data;
	t_complex		z;
	t_complex		c;
	int				i;
	double			zoom;
	int				max_ite;
	int				g;
	int				tmp;
	int				select;
}					t_q;

int					newton(t_q *q, int x, int y);
int					julia(t_q *q, int x, int y);
int					mandelbrot(t_q *q, int x, int y);
void				pxl2img(t_q *q, int x, int y, int color);
int					expose_fdf(t_q *q);
int					clear_image(t_q *q, int x, int y);
void				init(t_q *q);
int					fractal_it(t_q *q, int x, int y);
int					my_key_funct(int keycode, t_q *q);
int					ft_close(t_q *q);


#endif
