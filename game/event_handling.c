/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:39:31 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 19:35:29 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	move_player(t_window *window, double angle)
{
	window->player.x += cos(angle * PI / 180) * MOV_SPEED;
	window->player.y += sin(angle * PI / 180) * MOV_SPEED;
}

static void	rotate_player(t_window *window, double angle)
{
	window->player.dir += angle;
	if (window->player.dir < 0)
		window->player.dir += 360;
	if (window->player.dir >= 360)
		window->player.dir -= 360;
}

int check_collision(t_window *window, double old_x, double old_y, double new_x, double new_y)
{
	double delta_x = new_x - old_x;
	double delta_y = new_y - old_y;
	double dist = sqrt(delta_x * delta_x + delta_y * delta_y);

	if (dist == 0)
	return (0);

	double dir_x = delta_x / dist;
	double dir_y = delta_y / dist;
	double check_x = new_x + dir_x * 20.0;
	double check_y = new_y + dir_y * 20.0;
	int map_x = (int)(check_x / COL_S);
	int map_y = (int)(check_y / COL_S);

	if (map_x < 0 || map_x >= window->image->nb_cols ||
		map_y < 0 || map_y >= window->image->nb_rows)
		return (1);
	if (window->image->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int update_player(t_window *window)
{
	double new_x, new_y;
	double old_x = window->player.x; // store current position
	double old_y = window->player.y;
	if (window->mov.up)
	{
	    new_x = window->player.x + cos(window->player.dir * PI / 180) * MOV_SPEED;
	    new_y = window->player.y + sin(window->player.dir * PI / 180) * MOV_SPEED;
	    if (!check_collision(window, old_x, old_y, new_x, new_y))
	    {
	        window->player.x = new_x;
	        window->player.y = new_y;
	    }
	}
	if (window->mov.down)
	{
	    new_x = window->player.x - cos(window->player.dir * PI / 180) * MOV_SPEED;
	    new_y = window->player.y - sin(window->player.dir * PI / 180) * MOV_SPEED;
	    if (!check_collision(window, old_x, old_y, new_x, new_y))
	    {
	        window->player.x = new_x;
	        window->player.y = new_y;
	    }
	}
	if (window->mov.left)
	{
	    new_x = window->player.x + cos((window->player.dir - 90) * PI / 180) * MOV_SPEED;
	    new_y = window->player.y + sin((window->player.dir - 90) * PI / 180) * MOV_SPEED;
	    if (!check_collision(window, old_x, old_y, new_x, new_y))
	    {
	        window->player.x = new_x;
	        window->player.y = new_y;
	    }
	}
	if (window->mov.right)
	{
	    new_x = window->player.x + cos((window->player.dir + 90) * PI / 180) * MOV_SPEED;
	    new_y = window->player.y + sin((window->player.dir + 90) * PI / 180) * MOV_SPEED;
	    if (!check_collision(window, old_x, old_y, new_x, new_y))
	    {
	        window->player.x = new_x;
	        window->player.y = new_y;
	    }
	}
	if (window->mov.r_left)
	{
	    window->player.dir -= ROT_SPEED;
	    if (window->player.dir < 0)
	        window->player.dir += 360;
	}
	if (window->mov.r_right)
	{
	    window->player.dir += ROT_SPEED;
	    if (window->player.dir >= 360)
	        window->player.dir -= 360;
	}
	draw_scene(window->image, window);
	return (0);
}

int	key_release(int keycode, t_window *window)
{
	if (keycode == UP)
		window->mov.up = 0;
	if (keycode == DOWN)
		window->mov.down = 0;
	if (keycode == LEFT)
		window->mov.left = 0;
	if (keycode == RIGHT)
		window->mov.right = 0;
	if (keycode == R_ARROW)
		window->mov.r_right = 0;
	if (keycode == L_ARROW)
		window->mov.r_left = 0;
	return (0);
}
