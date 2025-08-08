/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:03 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/02 01:09:50 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_rectangular(char **map)
{
	size_t	w;
	int		i;

	w = ft_strlen(map[0]);
	i = 0;
	while (map[++i])
	{
		if (ft_strlen(map[i]) != w)
			return (0);
	}
	return (1);
}

static int	check_walls(char **map, size_t w, int h)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (int)w)
	{
		if (map[0][i] != '1' || map[h - 1][i] != '1')
			return (0);
		i++;
	}
	while (j < h)
	{
		if (map[j][0] != '1' || map[j][w - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

static int	check_components(char **map, int *p, int *e, int *c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				(*p)++;
			else if (map[i][j] == 'E')
				(*e)++;
			else if (map[i][j] == 'C')
				(*c)++;
			else if (map[i][j] != '0' && map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	if (*p == 1 && *e == 1 && *c >= 1)
		return (1);
	else
		return (0);
}

int	validate_map(char **map)
{
	int		h;
	size_t	w;
	int		p;
	int		e;
	int		c;

	if (!map || !map[0])
		return (0);
	h = 0;
	while (map[h])
		h++;
	if (!check_rectangular(map))
		return (0);
	w = ft_strlen(map[0]);
	if (!check_walls(map, w, h))
		return (0);
	p = 0;
	e = 0;
	c = 0;
	if (!check_components(map, &p, &e, &c))
		return (0);
	return (1);
}
