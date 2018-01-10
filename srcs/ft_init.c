/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:51:58 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/03/04 14:57:32 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_init_fdf_struct(t_fdf *fdf, char *file)
{
	if ((fdf->mapw = ft_linelenmax(file)) == 0)
		ft_error(1, fdf);
	if ((fdf->maph = ft_nbline(file)) == 0)
		ft_error(1, fdf);
	fdf->xo = IMG_W / 3;
	fdf->yo = IMG_H / 5;
	fdf->bpp = 0;
	fdf->linelen = 0;
	fdf->endian = 1;
	fdf->fill = 0;
	fdf->z = 1.0;
	fdf->cos = cos(2 * PI / (360 / 30));
	fdf->sin = sin(2 * PI / (360 / 30));
	fdf->zoom = 1.0;
	ft_initmap(fdf, file);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_W, WIN_H, file);
	fdf->img = mlx_new_image(fdf->mlx, IMG_W, IMG_H);
	fdf->data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->linelen, \
																&fdf->endian);
}

void	ft_init_line_struct(t_line *line, t_xy a, t_xy b)
{
	line->dx = abs(b.x - a.x);
	line->sx = a.x < b.x ? 1 : -1;
	line->dy = abs(b.y - a.y);
	line->sy = a.y < b.y ? 1 : -1;
	line->err = (line->dx > line->dy ? line->dx : -line->dy) / 2;
	line->e2 = line->err;
	line->l = sqrt(pow(line->dx, 2) + pow(line->dy, 2));
	line->color_multiplier = 1;
}

void	ft_free_map(t_fdf *fdf)
{
	int		i;

	i = -1;
	while (++i < fdf->maph && fdf->map)
		if (fdf->map[i])
			free(fdf->map[i]);
	if (fdf->map)
		free(fdf->map);
}

void	ft_print_commands(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 180, 0xC0C0C0, \
													"+ / -: zoomer / dezoomer");
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 155, 0xC0C0C0, \
												"fleches: deplacer le dessin");
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 130, 0xC0C0C0, \
															"w / s: z+ / z-");
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 105, 0xC0C0C0, \
												"r: reinitialiser le dessin");
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 80, 0xC0C0C0, \
													"p: changer de projection");
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 55, 0xC0C0C0, \
														"f: remplir les cases");
	mlx_string_put(fdf->mlx, fdf->win, 15, WIN_H - 30, 0xC0C0C0, \
																"ESC: quitter");
}
