/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 03:21:17 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 03:42:58 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	**dup_map(char **src)
{
	int		h;
	char	**dst;

	h = 0;
	while (src[h])
		h = h + 1;
	dst = (char **)ft_calloc((size_t)(h + 1), sizeof(char *));
	if (!dst)
		return (NULL);
	h = 0;
	while (src[h])
	{
		dst[h] = ft_strdup(src[h]);
		if (!dst[h])
		{
			free_map(dst);
			return (NULL);
		}
		h = h + 1;
	}
	return (dst);
}

static int	find_player_xy(char **map, int *sy, int *sx)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*sy = y;
				*sx = x;
				return (1);
			}
			x = x + 1;
		}
		y = y + 1;
	}
	return (0);
}

static void	count_cells_and_c(char **map, size_t *cells, int *total_c)
{
	int	y;
	int	x;

	*cells = 0;
	*total_c = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			*cells = *cells + 1;
			if (map[y][x] == 'C')
				*total_c = *total_c + 1;
			x = x + 1;
		}
		y = y + 1;
	}
}

bool	pathfind_verify_bonus(t_game *g)
{
	char	**tmp;
	size_t	cells;
	int		stats[3];
	int		sy;
	int		sx;

	tmp = dup_map(g->map);
	if (!tmp)
		return (false);
	count_cells_and_c(tmp, &cells, &stats[2]);
	if (cells == 0 || cells > (size_t)50000000)
		return (free_map(tmp), false);
	if (!find_player_xy(tmp, &sy, &sx))
		return (free_map(tmp), false);
	stats[0] = 0;
	stats[1] = 0;
	fill_map(tmp, sy, sx, &(t_fill_ctx){.stats = stats, .cap = cells});
	free_map(tmp);
	if (stats[0] != stats[2] || stats[1] == 0)
		return (false);
	return (true);
}
