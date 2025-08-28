/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind_fill_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 02:51:27 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/28 03:48:13 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	alloc_queues(size_t cap, t_q *q)
{
	q->qy = (int *)malloc(sizeof(int) * cap);
	if (!q->qy)
		return (0);
	q->qx = (int *)malloc(sizeof(int) * cap);
	if (!q->qx)
	{
		free(q->qy);
		return (0);
	}
	q->tail = 0;
	return (1);
}

static void	free_queues(t_q *q)
{
	if (q->qy)
		free(q->qy);
	if (q->qx)
		free(q->qx);
}

static void	add_to_queue(t_q *q, int y, int x)
{
	q->qy[q->tail] = y;
	q->qx[q->tail] = x;
	q->tail = q->tail + 1;
}

static void	check_and_add(char **m, t_q *q, int ny, int nx)
{
	if (!m[ny])
		return ;
	if (nx < 0)
		return ;
	if (!m[ny][nx])
		return ;
	if (m[ny][nx] == '1')
		return ;
	if (m[ny][nx] == 'V')
		return ;
	m[ny][nx] = 'V';
	add_to_queue(q, ny, nx);
}

void	fill_map(char **m, int sy, int sx, t_fill_ctx *ctx)
{
	t_q		q;
	size_t	head;
	int		y;
	int		x;

	if (!alloc_queues(ctx->cap, &q))
		return ;
	head = 0;
	m[sy][sx] = 'V';
	add_to_queue(&q, sy, sx);
	while (head < q.tail)
	{
		y = q.qy[head];
		x = q.qx[head];
		head = head + 1;
		if (m[y][x] == 'C')
			ctx->stats[0] = ctx->stats[0] + 1;
		if (m[y][x] == 'E')
			ctx->stats[1] = 1;
		check_and_add(m, &q, y, x - 1);
		check_and_add(m, &q, y, x + 1);
		check_and_add(m, &q, y - 1, x);
		check_and_add(m, &q, y + 1, x);
	}
	free_queues(&q);
}
