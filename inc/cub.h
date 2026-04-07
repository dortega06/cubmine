/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:05:19 by dortega-          #+#    #+#             */
/*   Updated: 2026/04/01 19:09:35 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/********************************[ macros ]************************************/

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK  64

# define A 97
# define W 119
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define PI 3.1415926535

/********************************[ libs ]**************************************/

# include "../mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
/*******************************[ structs ]************************************/

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*wnd;
	void	*img;

	char *data;
	int	bpp;
	int	size_line;
	int endian;
	t_player	player;

	char **map;
}	t_game;

/*******************************[ ft ]************************************/

void	init_player(t_player *player);
int key_realese(int keycode, t_player *player);
int key_press(int keycode, t_player *player);
void    move_player(t_player *player);

#endif
