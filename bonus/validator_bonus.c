/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 02:24:17 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/13 18:43:50 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	sl_map_dims(char **grid, int *w, int *h)
{
	int	i;
	int	k;

	if (!grid || !grid[0])
		return (0);
	i = 0;
	while (grid[i])
		i = i + 1;
	*h = i;
	k = 0;
	while (grid[0][k] != '\0')
		k = k + 1;
	*w = k;
	return (1);
}

static int	is_rectangular(char **grid, int w, int h)
{
	int	y;
	int	len;

	if (w <= 0 || h <= 0)
		return (0);
	y = 0;
	while (y < h)
	{
		len = 0;
		while (grid[y][len] != '\0')
			len = len + 1;
		if (len != w)
			return (0);
		y = y + 1;
	}
	return (1);
}

static int	is_walled(char **grid, int w, int h)
{
	int	x;
	int	y;

	if (w < 3 || h < 3)
		return (0);
	x = 0;
	while (x < w)
	{
		if (grid[0][x] != '1' || grid[h - 1][x] != '1')
			return (0);
		x = x + 1;
	}
	y = 1;
	while (y < h - 1)
	{
		if (grid[y][0] != '1' || grid[y][w - 1] != '1')
			return (0);
		y = y + 1;
	}
	return (1);
}

static int	scan_and_count(char **grid, int w, int h, int count[3])
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (!(grid[y][x] == '0' || grid[y][x] == '1' || grid[y][x] == 'C'
					|| grid[y][x] == 'E' || grid[y][x] == 'P'
					|| grid[y][x] == 'N'))
				return (0);
			if (grid[y][x] == 'P')
				count[0] = count[0] + 1;
			if (grid[y][x] == 'C')
				count[1] = count[1] + 1;
			if (grid[y][x] == 'E')
				count[2] = count[2] + 1;
			x = x + 1;
		}
		y = y + 1;
	}
	return (1);
}

bool	validator_check_bonus(t_game *g)
{
	char	**grid;
	int		w;
	int		h;
	int		cnt[3];

	grid = g->map;
	if (!sl_map_dims(grid, &w, &h))
		return (false);
	if (!is_rectangular(grid, w, h))
		return (false);
	if (!is_walled(grid, w, h))
		return (false);
	cnt[0] = 0;
	cnt[1] = 0;
	cnt[2] = 0;
	if (!scan_and_count(grid, w, h, cnt))
		return (false);
	if (cnt[0] != 1 || cnt[1] < 1 || cnt[2] < 1)
		return (false);
	return (true);
}
