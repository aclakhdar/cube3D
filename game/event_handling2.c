/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:28:27 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/12 00:03:50 by mbouras          ###   ########.fr       */
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

void	destroy_textures(t_data *img)
{
	if (img->north.img)
		mlx_destroy_image(img->mlx_ptr, img->north.img);
	if (img->south.img)
		mlx_destroy_image(img->mlx_ptr, img->south.img);
	if (img->east.img)
		mlx_destroy_image(img->mlx_ptr, img->east.img);
	if (img->west.img)
		mlx_destroy_image(img->mlx_ptr, img->west.img);
}

void	free_map(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	handle_escape(int keycode, t_window *window)
{
	if (keycode == ESC)
	{
		free_map(window->image->map);
		free(window->image->ea);
		free(window->image->we);
		free(window->image->so);
		free(window->image->no);
		destroy_textures(window->image);
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
