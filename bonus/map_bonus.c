/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:54:38 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/12 05:10:47 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	count_enemies(char **grid, int w, int h)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < w * h)
	{
		if (grid[i / w][i % w] == 'N')
			total = total + 1;
		i = i + 1;
	}
	return (total);
}

static void	fill_enemies(t_enemy *arr, char **grid, int w, int h)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < w * h)
	{
		if (grid[i / w][i % w] == 'N')
		{
			arr[k].x = i % w;
			arr[k].y = i / w;
			arr[k].dir = 1;
			k = k + 1;
		}
		i = i + 1;
	}
}

int	enemies_init(t_game *g, t_bonus *b)
{
	int		w;
	int		h;
	int		total;
	t_enemy	*arr;

	if (!sl_map_dims(g->map, &w, &h))
		return (0);
	total = count_enemies(g->map, w, h);
	b->enemies.count = total;
	b->enemies.w = w;
	b->enemies.h = h;
	if (total <= 0)
	{
		b->enemies.items = NULL;
		return (1);
	}
	arr = (t_enemy *)malloc((size_t)total * sizeof(t_enemy));
	if (arr == NULL)
	{
		b->enemies.count = 0;
		return (0);
	}
	fill_enemies(arr, g->map, w, h);
	b->enemies.items = arr;
	return (1);
}

void	enemies_free(t_bonus *b)
{
	if (b->enemies.items != NULL)
		free(b->enemies.items);
	b->enemies.items = NULL;
	b->enemies.count = 0;
}
