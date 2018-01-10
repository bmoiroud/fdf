/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:47:21 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/06/20 16:17:28 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define WIN_H		800
# define WIN_W		1200
# define IMG_H		WIN_H
# define IMG_W		WIN_W
# define ZOOM		0.9
# define PI			3.14159268
# define WHITE		16777215

typedef struct	s_xy
{
	int			x;
	int			y;
	int			color;
}				t_xy;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			l;
	int			color_multiplier;
}				t_line;

typedef struct	s_map
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_map;

typedef struct	s_fdf
{
	int			mapw;
	int			maph;
	int			fill;
	int			bpp;
	int			linelen;
	int			endian;
	int			iso;
	double		z;
	double		xo;
	double		yo;
	double		zoom;
	double		cos;
	double		sin;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	t_map		**map;
}				t_fdf;

int				ft_nbline(char *file);
int				ft_linelenmax(char *file);
void			ft_fill(t_fdf *fdf);
void			ft_draw(t_fdf *fdf);
void			ft_reset(t_fdf *fdf);
void			ft_refresh(t_fdf *fdf);
void			ft_free_map(t_fdf *fdf);
void			ft_iso_calc(t_fdf *fdf);
void			ft_caval_calc(t_fdf *fdf);
void			ft_move(t_fdf *fdf, int k);
void			ft_zoom(t_fdf *fdf, int k);
void			ft_print_commands(t_fdf *fdf);
void			ft_error(int error, t_fdf *fdf);
void			ft_move_height(t_fdf *fdf, int k);
void			ft_initmap(t_fdf *fdf, char *file);
void			ft_init_fdf_struct(t_fdf *fdf, char *file);
void			ft_init_line_struct(t_line *line, t_xy a, t_xy b);

#endif
