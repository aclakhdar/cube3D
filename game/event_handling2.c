/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:28:27 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 21:25:41 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	handle_key_press(int keycode, t_window *window)
{
	if (keycode == R_ARROW || keycode == L_ARROW || keycode == UP \
		|| keycode == DOWN || keycode == LEFT || keycode == RIGHT)
	{
		window->mov.moved = 1;
		if (keycode == R_ARROW)
			window->mov.r_right = 1;
		if (keycode == L_ARROW)
			window->mov.r_left = 1;
		if (keycode == UP)
			window->mov.up = 1;
		if (keycode == DOWN)
			window->mov.down = 1;
		if (keycode == LEFT)
			window->mov.left = 1;
		if (keycode == RIGHT)
			window->mov.right = 1;
	}
	return (0);
}

int	handle_escape(int keycode, t_window *window)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(window->mlx, window->image->img);
		mlx_destroy_image(window->mlx, window->img.img);
		mlx_destroy_window(window->mlx, window->win);
		if (window->mlx)
		{
			mlx_destroy_display(window->mlx);
			free(window->mlx);
		}
		exit(0);
	}
	return (0);
}

int	key_press(int keycode, t_window *window)
{
	handle_key_press(keycode, window);
	handle_escape(keycode, window);
	return (0);
}
