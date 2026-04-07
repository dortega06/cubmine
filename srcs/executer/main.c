/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:31 by dortega-          #+#    #+#             */
/*   Updated: 2026/04/03 18:44:39 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}

void	draw_map(t_game *game)
{
	char **map = game->map;
	int color = 0x0000FF;
	for (int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, color, game);
}

void	clear_img(t_game *game)
{
	for(int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
	}
}

char **get_map(void)
{
	char **map = malloc(sizeof(char *) * 6);
	map[0] = "111111";
	map[1] = "100001";
	map[2] = "100001";
	map[3] = "100001";
	map[4] = "111111";
	map[5] = NULL;
	return (map);
}

void	init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->wnd = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->wnd, game->img, 0, 0);
}

bool touch(float px, float py, t_game *game)
{
	int	x = px / BLOCK;
	int	y = py / BLOCK;

	if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)
		return true;

	// fuera del mapa => pared
	if (y < 0 || !game->map[y])
		return true;
	if (x < 0 || x >= (int)strlen(game->map[y]))
		return true;
	if (game->map[y][x] == '1')
		return (true);
	return false;
}

void	draw_line(t_player *player, t_game *game, float start_x)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
/*	float dist = distance(ray_x - player->x, ray_y - player->y);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int	end = start_y + height;*/
}

int	draw_loop(t_game *game)
{
	t_player	*player = &game->player;
	move_player(player);
	clear_img(game);
	draw_square(player->x, player->y, 10, 0xFF69B4, game);
	draw_map(game);

/*	float ray_x = player->x;
	float ray_y = player->y;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}*/
	float fraction = PI / 3/ WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->wnd, game->img, 0, 0);
	return 0;
}

int	main(void)
{
	t_game	game;
	init_game(&game);
	mlx_hook(game.wnd, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.wnd, 3, 1L<<1, key_realese, &game.player);
	
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
