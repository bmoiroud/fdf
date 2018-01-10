/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:32:55 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/20 16:17:32 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_putpixel(t_fdf *fdf, int y, int x, int color)
{
	int		i;

	i = 0;
	if (x < IMG_W && y < IMG_H && x >= 0 && y >= 0)
	{
		i = fdf->linelen * y + x * (fdf->bpp / 8);
		fdf->data[i] = color & 0xff;
		fdf->data[++i] = color >> 8 & 0xff;
		fdf->data[++i] = color >> 16 & 0xff;
	}
}

void	ft_drawlines(t_fdf *fdf, t_xy a, t_xy b)
{
	t_line		line;

	ft_init_line_struct(&line, a, b);
	while (1)
	{
		ft_putpixel(fdf, a.y, a.x, b.color);
		if (a.x == b.x && a.y == b.y)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			a.x += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			a.y += line.sy;
		}
	}
}

void	ft_trace2(t_fdf *fdf, int x, int y)
{
	t_xy	a;
	t_xy	b;

	if (y < fdf->maph - 1 && x < fdf->mapw - 1 && fdf->fill == 1)
	{
		a.x = fdf->map[y][x].x;
		a.y = fdf->map[y][x].y;
		a.color = fdf->map[y][x].color;
		b.x = fdf->map[y + 1][x + 1].x;
		b.y = fdf->map[y + 1][x + 1].y;
		b.color = fdf->map[y + 1][x + 1].color;
		ft_drawlines(fdf, a, b);
	}
}

void	ft_trace(t_fdf *fdf, int x, int y)
{
	t_xy	a;
	t_xy	b;

	if (x < fdf->mapw - 1)
	{
		a.x = fdf->map[y][x].x;
		a.y = fdf->map[y][x].y;
		a.color = fdf->map[y][x].color;
		b.x = fdf->map[y][x + 1].x;
		b.y = fdf->map[y][x + 1].y;
		b.color = fdf->map[y][x + 1].color;
		ft_drawlines(fdf, a, b);
	}
	if (y < fdf->maph - 1)
	{
		a.x = fdf->map[y][x].x;
		a.y = fdf->map[y][x].y;
		a.color = fdf->map[y][x].color;
		b.x = fdf->map[y + 1][x].x;
		b.y = fdf->map[y + 1][x].y;
		b.color = fdf->map[y + 1][x].color;
		ft_drawlines(fdf, a, b);
	}
	ft_trace2(fdf, x, y);
}

void	ft_draw(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->maph && i < IMG_H)
	{
		j = 0;
		while (j < fdf->mapw && j < IMG_W)
		{
			ft_trace(fdf, j, i);
			j++;
		}
		i++;
	}
}
