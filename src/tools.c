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
	int	color[49] = { 0x00FF0900, 0x00E8001E, 0x00FF0060, 0x00E80091, 0x00FF00DE, 0x00D900E8, 0x00CD00FF, 0x009B00E8, 0x008800FF, 0x005C00E8, 0x004300FF, 0x001E00E8, 0x000001FF, 0x00001FE8, 0x000043FF, 0x00005BE8, 0x000085FF, 0x000097E8, 0x0000C7FF, 0x0000D3E8, 0x0000FFF4, 0x0000E8BE, 0x0000FFAD, 0x0000E87D, 0x0000FF66, 0x0000E83C, 0x0000FF1F, 0x0005E800, 0x0032FF00, 0x0055E800, 0x008AFF00, 0x00A5E800, 0x00E1FF00,	0x00E8E400, 0x00FFEE00, 0x00E8CD00, 0x00FFD500, 0x00E8B700, 0x00FFBC00, 0x00E8A000, 0x00FFA300, 0x00E88900, 0x00FF8500, 0x00E86900, 0x00FF6100, 0x00E84800, 0x00FF3C00, 0x00E82600, 0x00FF1800 };
	while (i > 49)
		i = i - 49;
	if (q->frac)
		color[i] = color[i] * q->frac;
	return (color[i]);
	
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
