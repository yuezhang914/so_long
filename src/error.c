/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:20 by yzhang2           #+#    #+#             */
/*   Updated: 2025/08/12 15:12:21 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_free_all(t_game *g)
{
	if (!g)
		return ;
	if (g->fd >= 0)
		close(g->fd);
	free_images(g);
	free_map(g->map);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

void	perror_exit(t_game *g, const char *msg)
{
	if (!g || !msg)
		return ;
	ft_printf("Error\n%s\n", msg);
	sl_free_all(g);
	exit(EXIT_FAILURE);
}

int	clean_exit(void *param)
{
	sl_free_all((t_game *)param);
	exit(EXIT_SUCCESS);
	return (0);
}
