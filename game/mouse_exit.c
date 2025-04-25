/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:38:23 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/12 19:40:25 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_exit(t_window *window)
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
	return (0);
}
