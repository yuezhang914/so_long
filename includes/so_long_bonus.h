/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:54:15 by yzhang2           #+#    #+#             */
/*   Updated: 2025/09/22 14:11:50 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "so_long.h"
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BONUS_HUD_MARGIN
#  define BONUS_HUD_MARGIN 8
# endif

# ifndef BONUS_ENEMY_STEP_TICKS
#  define BONUS_ENEMY_STEP_TICKS 30000
# endif

typedef struct s_v2i
{
	int			x;
	int			y;
}				t_v2i;

typedef struct s_hud
{
	char		step_buf[32];
	bool		dirty;
	t_v2i		pos_px;
}				t_hud;

typedef struct s_anim
{
	void		**images;
	int			total;
	int			pos;
}				t_anim;

typedef struct s_enemy
{
	int			x;
	int			y;
	int			dir;
}				t_enemy;

typedef struct s_enemies
{
	t_enemy		*items;
	int			count;
	int			w;
	int			h;
	t_anim		anim;
}				t_enemies;

typedef struct s_bonus
{
	t_anim		player_anim;
	void		*player_imgs[2];

	t_enemies	enemies;
	void		*enemy_imgs[2];

	t_hud		hud;

	t_img		player2;
	t_img		enemy1;
	t_img		enemy2;

	int			lost;
	bool		initialized;
}				t_bonus;

typedef struct s_hookctx
{
	t_game		*g;
	t_bonus		*b;
	int			last_moves;
	int			need_redraw;
	int			frame_acc;
}				t_hookctx;

typedef struct s_fill_ctx
{
	int			*stats;
	size_t		cap;
}				t_fill_ctx;

typedef struct s_q
{
	int			*qy;
	int			*qx;
	size_t		tail;
}				t_q;

int				sl_map_dims(char **grid, int *w, int *h);
bool			validator_check_bonus(t_game *g);
void			fill_map(char **m, int sy, int sx, t_fill_ctx *ctx);
bool			pathfind_verify_bonus(t_game *g);

void			anim_init(t_anim *a, void **images, int total);
void			anim_flip(t_anim *a);
void			*anim_get_frame(const t_anim *a);

int				enemies_init(t_game *g, t_bonus *b);
void			enemies_free(t_bonus *b);
void			enemies_step_once(t_game *g, t_bonus *b);

int				collide_check_lose(t_game *g, t_bonus *b);

int				bonus_images_load(t_game *g, t_bonus *b);
void			bonus_images_free(t_game *g, t_bonus *b);

void			hud_init(t_game *g, t_bonus *b);
void			hud_update(t_game *g, t_bonus *b);
void			render_bonus_frame(t_game *g, t_bonus *b);

void			*hooks_bonus_install(t_game *g, t_bonus *b);
void			hooks_bonus_free(void *opaque);

void			lose_and_quit(t_hookctx *c);
int				validate_map(char **map);
int				calc_view_size(t_game *g, int sw, int sh);
int				create_window_if_needed(t_game *g);

#endif
