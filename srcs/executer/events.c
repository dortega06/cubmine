/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 19:07:38 by dortega-          #+#    #+#             */
/*   Updated: 2026/05/02 17:56:46 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

/*
** Libera la memoria reservada para las rutas de las texturas de la estructura game.
*/
static void	free_texture_paths(t_game *game)
{
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.west)
		free(game->textures.west);
	if (game->textures.east)
		free(game->textures.east);
}

/*
** Libera todos los recursos asociados al juego, como imágenes, ventanas, mapas y texturas.
*/
static void	free_game_resources(t_game *game)
{
	if (game->texture_imgs)
		free_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->wnd)
		mlx_destroy_window(game->mlx, game->wnd);
	if (game->map)
		free(game->map);
	free_texture_paths(game);
}

/*
** Cierra el juego de forma segura liberando todos los recursos y cerrando la ventana.
*/
int	close_game(t_game *game)
{
	if (!game)
		exit(0);

	free_game_resources(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}

	exit(0);
	return (0);
}
