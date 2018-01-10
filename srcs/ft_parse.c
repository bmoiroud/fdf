/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:42:42 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/04/27 19:13:35 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_linelenmax(char *file)
{
	int		i;
	int		l;
	int		max;
	int		fd;
	char	*str;

	max = 0;
	i = -1;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &str) == 1)
	{
		l = 0;
		while (str[++i])
			if (str[i] && str[i] != ' ' && str[i] <= '9' && str[i] >= '0')
			{
				l++;
				while (str[i] && str[i] != ' ')
					i++;
			}
		max = ((l > max) ? l : max);
		i = 0;
		free(str);
	}
	close(fd);
	return (max);
}

int		ft_nbline(char *file)
{
	int		i;
	int		fd;
	char	*s;

	fd = open(file, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &s) == 1)
	{
		free(s);
		i++;
	}
	close(fd);
	return (i);
}

void	ft_mapdata(t_fdf *fdf, char **tab, int y)
{
	int		i;
	int		j;

	i = -1;
	while (tab[++i] && i < fdf->mapw)
	{
		j = 0;
		fdf->map[y][i].x = 0;
		fdf->map[y][i].y = 0;
		while (tab[i][j] <= '9' && tab[i][j] >= '0')
			j++;
		if (tab[i][j] == ',')
		{
			tab[i][j] = '\0';
			fdf->map[y][i].color = ft_atoi_base(tab[i] + j + 1, 16);
		}
		else if (tab[i][j] == '\0' || ((tab[i][j] >= '0' && tab[i][j] <= '9') \
														|| tab[i][j] == '-'))
			fdf->map[y][i].color = WHITE;
		else
			fdf->map[y][i].color = 0;
		fdf->map[y][i].z = ft_atoi(tab[i]);
	}
}

void	ft_initmap(t_fdf *fdf, char *file)
{
	int		fd;
	int		i;
	char	*line;
	char	**tab;

	i = -1;
	if (!(fdf->map = malloc(fdf->maph * sizeof(t_map))))
		exit(EXIT_FAILURE);
	while (++i < fdf->maph)
		if (!(fdf->map[i] = malloc(fdf->mapw * sizeof(t_map))))
			exit(EXIT_FAILURE);
	if (!(fd = open(file, O_RDONLY)))
		ft_error(1, fdf);
	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!(tab = ft_strsplit(line, ' ')))
			ft_error(data, 3);
		ft_mapdata(fdf, tab, i);
		free(line);
		i++;
	}
	close(fd);
}
