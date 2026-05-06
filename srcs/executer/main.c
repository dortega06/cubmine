/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:31 by dortega-          #+#    #+#             */
/*   Updated: 2026/05/02 18:47:42 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"
#include <math.h>

/*
** Limpia la imagen de la ventana, poniendo todos los píxeles a negro.
*/
void	clear_img(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

/*
** Carga todas las texturas necesarias para el juego desde los archivos correspondientes.
*/
static void	load_all_textures(t_game *game)
{
	load_texture(game, 0, "./textures/redbrick.xpm");
	load_texture(game, 1, "./textures/greystone.xpm");
	load_texture(game, 2, "./textures/wood.xpm");
	load_texture(game, 3, "./textures/mossy.xpm");
}/*
char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}*/

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 15);
    map[0] = "1111111111111111111";
    map[1] = "1000000000000000001";
    map[2] = "1001110000111000001";
    map[3] = "1001010000101000001";
    map[4] = "1001110011101000001";
    map[5] = "1000000000000000001";
    map[6] = "1011111011111100001";
    map[7] = "1010001010001000001";
    map[8] = "1010101010101000001";
    map[9] = "1010001010001000001";
    map[10] = "1011111011111100001";
    map[11] = "1000000000000000001";
    map[12] = "1000111000111000001";
    map[13] = "1111111111111111111";
    map[14] = NULL;
    return (map);
}

/*
** Inicializa todas las variables y recursos necesarios para empezar el juego.
*/
void	init_game(t_game *game)
{
	init_player(&game->player);
	init_textures(game);
	game->map = get_map();

	game->map_height = 0;
	while (game->map[game->map_height])
		game->map_height++;

	game->mlx = mlx_init();
	game->wnd = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	load_all_textures(game);
	mlx_put_image_to_window(game->mlx, game->wnd, game->img, 0, 0);
}

/*
** Verifica si la posición indicada choca con una pared o está fuera de los límites del mapa.
**
** @param	px		Coordenada X a comprobar.
** @param	py		Coordenada Y a comprobar.
** @param	game	Puntero a la estructura principal del juego.
** @return			true si hay colisión o fuera de límites, false en caso contrario.
*/
bool touch(double px, double py, t_game *game)
{
	int	x = px / BLOCK;
	int	y = py / BLOCK;

	if (px < 0 || py < 0 || px >= WIDTH || py >= HEIGHT)
		return true;
	if (y < 0 || y >= 100)
		return true;
	if (!game->map || !game->map[y])
		return true;
	if (x < 0 || x >= (int)strlen(game->map[y]))
		return true;
	if (game->map[y][x] == '1')
		return true;
	return false;
}

/*
** Calcula la distancia corregida entre dos puntos en relación al ángulo del jugador.
**
** @param	x1		Coordenada X del primer punto.
** @param	y1		Coordenada Y del primer punto.
** @param	x2		Coordenada X del segundo punto.
** @param	y2		Coordenada Y del segundo punto.
** @param	game	Puntero a la estructura principal del juego.
** @return			Distancia corregida.
*/
double	fixed_distance(double x1, double y1, double x2, double y2, t_game *game)
{
	double delta_x = x2 - x1;
	double delta_y = y2 - y1;
	double angle = atan2(delta_y, delta_x) - game->player.angle;
	double fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}

/*
** Punto de entrada principal del programa. Inicializa el juego y lanza el bucle principal de eventos.
*/
int	main(void)
{
	t_game	game;

	memset(&game, 0, sizeof(t_game));

	init_game(&game);
	mlx_hook(game.wnd, 2, 1L<<0, key_press, &game);
	mlx_hook(game.wnd, 3, 1L<<1, key_realese, &game);
	
	mlx_hook(game.wnd, 17, 0, close_game, &game);
	
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
