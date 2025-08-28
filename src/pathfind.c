/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:42:52 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/02 03:27:34 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**dup_map(char **src)
{
	int		h;
	char	**des;

	h = 0;
	while (src[h])
		h++;
	des = ft_calloc(h + 1, sizeof(char *));
	if (!des)
		return (NULL);
	h = 0;
	while (src[h])
	{
		des[h] = ft_strdup(src[h]);
		if (!des[h])
			return (free_map(des), NULL);
		h++;
	}
	return (des);
}

static void	flood_fill(char **map, int y, int x)
{
	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
}

static int	scan_result(char **map)
{
	int	x;
	int	y;
	int	e_left;
	int	c_left;

	y = 0;
	e_left = 0;
	c_left = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				c_left++;
			else if (map[y][x] == 'E')
				e_left++;
			x++;
		}
		y++;
	}
	if (c_left == 0 && e_left == 0)
		return (1);
	else
		return (0);
}

int	find_player(char **map, int *py, int *px)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
			{
				*py = y;
				*px = x;
				return (1);
			}
		}
	}
	return (0);
}

int	is_path_valid(char **map)
{
	int		x;
	int		y;
	char	**tmp;
	int		valid;

	if (!find_player(map, &y, &x))
		return (0);
	tmp = dup_map(map);
	if (!tmp)
		return (0);
	flood_fill(tmp, y, x);
	valid = scan_result(tmp);
	free_map(tmp);
	return (valid);
}
