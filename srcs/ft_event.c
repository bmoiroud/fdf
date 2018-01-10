/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 16:39:21 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/03/03 18:50:12 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_zoom(t_fdf *fdf, int k)
{
	if (k == 69)
		fdf->zoom /= ZOOM;
	else
		fdf->zoom *= ZOOM;
	if (fdf->zoom < 0.000001)
		fdf->zoom = 0.000001;
	ft_refresh(fdf);
}

void	ft_move(t_fdf *fdf, int k)
{
	if (k == 123)
		fdf->xo -= 30 / fdf->zoom;
	else if (k == 124)
		fdf->xo += 30 / fdf->zoom;
	else if (k == 125)
		fdf->yo += 30 / fdf->zoom;
	else if (k == 126)
		fdf->yo -= 30 / fdf->zoom;
	ft_refresh(fdf);
}

void	ft_reset(t_fdf *fdf)
{
	fdf->xo = IMG_W / 3;
	fdf->yo = IMG_H / 5;
	fdf->z = 1.0;
	fdf->fill = 0;
	fdf->zoom = 1.0;
	ft_refresh(fdf);
}

void	ft_fill(t_fdf *fdf)
{
	fdf->fill++;
	if (fdf->fill == 2)
		fdf->fill = 0;
	ft_refresh(fdf);
}

void	ft_move_height(t_fdf *fdf, int k)
{
	if (k == 13)
		fdf->z += 0.2;
	else
		fdf->z -= 0.2;
	ft_refresh(fdf);
}
