/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:12:05 by pdurand           #+#    #+#             */
/*   Updated: 2017/05/30 19:12:06 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractal.h"

int		getcolor(int i, t_q *q)
{
	int		colortmp;

	while (i > 48)
		i = i - 49;
	if (q->fracolorize)
	{
		colortmp = q->colortab[i];
		colortmp = colortmp * q->fracolorize;
		return (colortmp);
	}
	return (q->colortab[i]);
}

void	populatecolortab(t_q *q)
{
	q->colortab[0] = 0x00FF0900;
	q->colortab[1] = 0x00E8001E;
	q->colortab[2] = 0x00FF0060;
	q->colortab[3] = 0x00E80091;
	q->colortab[4] = 0x00FF00DE;
	q->colortab[5] = 0x00D900E8;
	q->colortab[6] = 0x00CD00FF;
	q->colortab[7] = 0x009B00E8;
	q->colortab[8] = 0x008800FF;
	q->colortab[9] = 0x005C00E8;
	q->colortab[10] = 0x004300FF;
	q->colortab[11] = 0x001E00E8;
	q->colortab[12] = 0x000001FF;
	q->colortab[13] = 0x00001FE8;
	q->colortab[14] = 0x000043FF;
	q->colortab[15] = 0x00005BE8;
	q->colortab[16] = 0x000085FF;
	q->colortab[17] = 0x000097E8;
	q->colortab[18] = 0x0000C7FF;
	q->colortab[19] = 0x0000D3E8;
	q->colortab[20] = 0x0000FFF4;
	q->colortab[21] = 0x0000E8BE;
	q->colortab[22] = 0x0000FFAD;
	q->colortab[23] = 0x0000E87D;
	populatecolortab2(q);
}

void	populatecolortab2(t_q *q)
{
	q->colortab[24] = 0x0000FF66;
	q->colortab[25] = 0x0000E83C;
	q->colortab[26] = 0x0000FF1F;
	q->colortab[27] = 0x0005E800;
	q->colortab[28] = 0x0032FF00;
	q->colortab[29] = 0x0055E800;
	q->colortab[30] = 0x008AFF00;
	q->colortab[31] = 0x00A5E800;
	q->colortab[32] = 0x00E1FF00;
	q->colortab[33] = 0x00E8E400;
	q->colortab[34] = 0x00FFEE00;
	q->colortab[35] = 0x00E8CD00;
	q->colortab[36] = 0x00FFD500;
	q->colortab[37] = 0x00E8B700;
	q->colortab[38] = 0x00FFBC00;
	q->colortab[39] = 0x00E8A000;
	q->colortab[40] = 0x00FFA300;
	q->colortab[41] = 0x00E88900;
	q->colortab[42] = 0x00FF8500;
	q->colortab[43] = 0x00E86900;
	q->colortab[44] = 0x00FF6100;
	q->colortab[45] = 0x00E84800;
	q->colortab[46] = 0x00FF3C00;
	q->colortab[47] = 0x00E82600;
	q->colortab[48] = 0x00FF1800;
}

void	pxl2img(t_q *q, int x, int y, int color)
{
	if (x > q->height || x < 0 || y > q->width || y < 0)
		return ;
	*(int *)&q->data[(y * q->len) + (x * (q->bpp / 8))] = color;
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*s01;
	unsigned char	*s02;

	i = 0;
	s01 = (unsigned char *)s1;
	s02 = (unsigned char *)s2;
	while ((s01[i] != '\0' || s02[i] != '\0') && (s01[i] == s02[i]))
		i++;
	return (s01[i] - s02[i]);
}
