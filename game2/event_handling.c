/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:22:38 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/10 19:24:23 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void update_camera(t_camera *camera, t_move *mov) {
	double moveSpeed = MOV_SPEED;
	double rotSpeed = ROT_SPEED;

	if (mov->up) {
		camera->x += camera->dirX * moveSpeed;
		camera->y += camera->dirY * moveSpeed;
	}
	if (mov->down) {
		camera->x -= camera->dirX * moveSpeed;
		camera->y -= camera->dirY * moveSpeed;
	}
	if (mov->left) {
		double oldDirX = camera->dirX;
		camera->dirX = camera->dirX * cos(rotSpeed) - camera->dirY * sin(rotSpeed);
		camera->dirY = oldDirX * sin(rotSpeed) + camera->dirY * cos(rotSpeed);
		double oldPlaneX = camera->planeX;
		camera->planeX = camera->planeX * cos(rotSpeed) - camera->planeY * sin(rotSpeed);
		camera->planeY = oldPlaneX * sin(rotSpeed) + camera->planeY * cos(rotSpeed);
	}
	if (mov->right) {
		double oldDirX = camera->dirX;
		camera->dirX = camera->dirX * cos(-rotSpeed) - camera->dirY * sin(-rotSpeed);
		camera->dirY = oldDirX * sin(-rotSpeed) + camera->dirY * cos(-rotSpeed);
		double oldPlaneX = camera->planeX;
		camera->planeX = camera->planeX * cos(-rotSpeed) - camera->planeY * sin(-rotSpeed);
		camera->planeY = oldPlaneX * sin(-rotSpeed) + camera->planeY * cos(-rotSpeed);
	}
}

int	update_player(t_window *window) //updating player position and redrawing the sceen
{
	if (window->mov.up)
	{
		window->player.x += cos(window->player.dir * PI / 180) * MOV_SPEED;
		window->player.y += sin(window->player.dir * PI / 180) * MOV_SPEED;
	}
	if (window->mov.down)
	{
		window->player.x -= cos(window->player.dir * PI / 180) * MOV_SPEED;
		window->player.y -= sin(window->player.dir * PI / 180) * MOV_SPEED;
	}
	if (window->mov.left)
	{
		window->player.x += cos((window->player.dir - 90) * PI / 180) * MOV_SPEED;
		window->player.y += sin((window->player.dir - 90) * PI / 180) * MOV_SPEED;
	}
	if (window->mov.right)
	{
		window->player.x += cos((window->player.dir + 90) * PI / 180) * MOV_SPEED;
		window->player.y += sin((window->player.dir + 90) * PI / 180) * MOV_SPEED;
	}
	if (window->mov.r_left) //fham hadi mzyan
	{
		window->player.dir -= ROT_SPEED;
		if (window->player.dir < 0)
			window->player.dir += 360;
	}
	if (window->mov.r_right)
	{
		if (window->player.dir >= 360)
			window->player.dir = 0;
		window->player.dir += ROT_SPEED;
	}
	update_camera(&window->camera, &window->mov);
	draw_scene(&window->img, window);
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

int	key_press(int keycode, t_window *window)
{
	if (keycode == R_ARROW)
	{
		window->mov.r_right = 1;
		window->mov.moved = 1;
	}
	if (keycode == L_ARROW)
	{
		window->mov.moved = 1;
		window->mov.r_left = 1;
	}
	if (keycode == UP)
	{
		window->mov.up = 1;
		window->mov.moved = 1;
	}
	if (keycode == DOWN)
	{
		window->mov.down = 1;
		window->mov.moved = 1;
	}
	if (keycode == LEFT)
	{
		window->mov.left = 1;
		window->mov.moved = 1;
	}
	if (keycode == RIGHT)
	{
		window->mov.right = 1;
		window->mov.moved = 1;
	}
	if (keycode == ESC)//free here
	{
		mlx_destroy_image(window->mlx, window->img.img);
		mlx_destroy_window(window->mlx, window->win);
		exit(0);
	}
	// printf("keycode: %d\n", keycode);
	return (0);
}
