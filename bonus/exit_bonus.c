/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:43:16 by yzhang2           #+#    #+#             */
/*   Updated: 2025/10/09 17:39:48 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	lose_and_quit(t_hookctx *c)
{
	write(2, "You lose\n", 9);
	enemies_free(c->b);
	bonus_images_free(c->g, c->b);
	sl_free_all(c->g);
	hooks_bonus_free((void *)c);
	exit(0);
}

void	win_and_quit(t_hookctx *c)
{
	write(1, "You win\n", 8);
	enemies_free(c->b);
	bonus_images_free(c->g, c->b);
	sl_free_all(c->g);
	hooks_bonus_free((void *)c);
	exit(0);
}
