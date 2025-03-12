/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:40:18 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/12 19:38:57 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

float	degree_to_radian(float degree)
{
	return (degree * (PI / 180));
}

void	init_player(t_player *player, t_data *img)
{
	player->x = img->player.x;
	player->y = img->player.y;
	player->dir = img->dir;
}

void	game(t_data *img)
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_window	window;

	init_player(&player, img);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "ULTRAKILL");
	img->img = mlx_new_image(mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	img->mlx_ptr = mlx;
	window.mlx = mlx;
	load_textures(img);
	window.player = player;
	window.win = win;
	window.img = *img;
	window.mov = (t_move){0, 0, 0, 0, 0};
	window.image = img;
	draw_scene(img, &window);
	mlx_hook(win, 2, 1L << 0, key_press, &window);
	mlx_hook(win, 3, 1L << 1, key_release, &window);
	mlx_hook(win, 17, 0, mouse_exit, &window);
	mlx_loop_hook(mlx, update_player, &window);
	mlx_loop(mlx);
}
