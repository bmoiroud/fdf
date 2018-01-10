/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:56:26 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/03/04 14:37:07 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_caval_calc(t_fdf *fdf)
{
	int		i;
	int		j;
	double	zoom;

	zoom = fdf->zoom * 1.5;
	i = -1;
	while (++i < fdf->maph && i < IMG_H)
	{
		j = -1;
		while (++j < fdf->mapw && j < IMG_W)
		{
			fdf->map[i][j].x = ((fdf->xo + (j * fdf->cos * zoom) - \
					(i * fdf->cos * zoom))) + ((10 * WIN_W / WIN_H) * j * zoom);
			fdf->map[i][j].y = (((fdf->yo + (j * fdf->sin * zoom)) - \
				(i * fdf->sin * zoom) - ((fdf->map[i][j].z * fdf->z) * (WIN_W /\
						WIN_H) * zoom))) + ((10 * WIN_W / WIN_H) * i * zoom);
		}
	}
}

void	ft_iso_calc(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->maph)
	{
		j = -1;
		while (++j < fdf->mapw)
		{
			fdf->map[i][j].x = ((j * 15) - (i * 15)) * fdf->zoom + 1 + fdf->xo;
			fdf->map[i][j].y = ((-(fdf->map[i][j].z * fdf->z * fdf->zoom) +\
				((j * 15) + (i * 15)) * fdf->zoom) + 1) + fdf->yo;
		}
	}
}
