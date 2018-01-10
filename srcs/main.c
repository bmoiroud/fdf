/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:39:22 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/03/04 14:38:12 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_error(int error, t_fdf *fdf)
{
	if (error == 1)
		ft_putstr("invalid map\n");
	if (fdf->img && fdf->win)
		mlx_destroy_image(fdf->win, fdf->img);
	ft_free_map(fdf);
	exit(EXIT_FAILURE);
}

void	ft_refresh(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, IMG_W, IMG_H);
	if (fdf->iso == 1)
		ft_iso_calc(fdf);
	else
		ft_caval_calc(fdf);
	ft_draw(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	ft_print_commands(fdf);
}

void	ft_free_all(t_fdf *fdf)
{
	ft_free_map(fdf);
	mlx_destroy_image(fdf->mlx, fdf->img);
	exit(EXIT_SUCCESS);
}

int		keyfunct(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == 53)
		ft_free_all((t_fdf *)param);
	else if (key == 69 || key == 78)
		ft_zoom((t_fdf *)param, key);
	else if (key >= 123 && key <= 126)
		ft_move((t_fdf *)param, key);
	else if (key == 15)
		ft_reset((t_fdf *)param);
	else if (key == 3)
		ft_fill((t_fdf *)param);
	else if (key == 13 || key == 1)
		ft_move_height((t_fdf *)param, key);
	else if (key == 35)
	{
		fdf->iso = (++fdf->iso % 2);
		ft_refresh(fdf);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac == 1)
		ft_putstr("usage: ./fdf map.fdf\n");
	else
	{
		ft_init_fdf_struct(&fdf, av[1]);
		if (fdf.map == NULL)
			ft_error(1, &fdf);
		ft_caval_calc(&fdf);
		ft_draw(&fdf);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
		ft_print_commands(&fdf);
		mlx_key_hook(fdf.win, keyfunct, (void *)&fdf);
		mlx_loop(fdf.mlx);
	}
	return (0);
}
