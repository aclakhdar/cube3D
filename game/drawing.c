/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:41:57 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/11 18:35:55 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_wall_properties(t_window *window, t_data *img, int i, t_tex **tex)
{
	if (window->f_line[i].type == HOR)
	{
		img->wall_x = fmod(window->f_line[i].x, COL_S) / COL_S;
		if (window->f_line[i].y > window->player.y)
			*tex = &img->south;
		else
			*tex = &img->north;
	}
	else
	{
		img->wall_x = fmod(window->f_line[i].y, COL_S) / COL_S;
		if (window->f_line[i].x > window->player.x)
			*tex = &img->east;
		else
			*tex = &img->west;
	}
	if (img->wall_x < 0)
		img->wall_x = 0;
	if (img->wall_x >= 1)
		img->wall_x = 0.999;
	img->tex_x = (int)(img->wall_x * ((*tex)->width - 1));
	if (img->tex_x < 0)
		img->tex_x = 0;
	if (img->tex_x >= (*tex)->width)
		img->tex_x = (*tex)->width - 1;
}

void	draw_3d(t_window *window, t_data *img, int i)
{
	img->screen_height = WINDOW_HEIGHT;
	if (window->f_line[i].dist < 0.0001)
		img->dist = 0.0001;
	else
		img->dist = window->f_line[i].dist;
	img->wall_height = (int)((COL_S * D_PLAN) / img->dist);
	img->wall_top = (img->screen_height / 2) - (img->wall_height / 2);
	img->wall_bottom = (img->screen_height / 2) + (img->wall_height / 2);
	set_wall_properties(window, img, i, &img->tex);
	img->y = img->wall_top - 1;
	while (++img->y < img->wall_bottom)
	{
		if (img->y >= 0 && img->y < img->screen_height && window->f_line[i].hit)
		{
			img->tex_y = ((double)(img->y - img->wall_top) / \
				img->wall_height) * (img->tex->height - 1);
			if (img->tex_y < 0)
				img->tex_y = 0;
			if (img->tex_y >= img->tex->height)
				img->tex_y = img->tex->height - 1;
			img->color = get_pixel(img->tex, img->tex_x, (int)img->tex_y);
			if (img->color != -1)
				my_mlx_pixel_put(img, i, img->y, img->color);
		}
	}
}

void	calculate_ray(t_window *window, t_data *img, int i)
{
	window->h_line[i] = horizontal_line(window, img->ray_angle, img);
	window->v_line[i] = vertical_line(window, img->ray_angle, img);
	if (window->v_line[i].dist <= window->h_line[i].dist)
		window->f_line[i] = window->v_line[i];
	else
		window->f_line[i] = window->h_line[i];
	window->f_line[i].dist = window->f_line[i].dist * \
		cos(degree_to_radian(window->player.dir - img->ray_angle));
	draw_3d(window, img, i);
}

void	dda_init(t_window *window, t_data *img)
{
	float	j;
	int		ray_num;
	int		i;

	j = window->player.dir - (FOV / 2.0);
	ray_num = WINDOW_WIDTH;
	img->degree = (float)FOV / (ray_num - 1);
	i = 0;
	while (i < ray_num)
	{
		img->ray_angle = j;
		if (img->ray_angle < 0)
			img->ray_angle += 360;
		if (img->ray_angle >= 360)
			img->ray_angle -= 360;
		calculate_ray(window, img, i);
		j += img->degree;
		i++;
	}
}

void	draw_scene(t_data *img, t_window *window)
{
	static int	i;

	if (window->mov.r_right || window->mov.r_left || window->mov.up \
		|| window->mov.down || window->mov.left || window->mov.right || !i)
	{
		window->mov.moved = 0;
		if (window->img.img && i)
			mlx_destroy_image(window->mlx, window->img.img);
		window->img.img = mlx_new_image(window->mlx, 1920, 1080);
		window->img.addr = mlx_get_data_addr(window->img.img, \
			&window->img.bits_per_pixel, \
			&window->img.line_length, &window->img.endian);
		draw_background(img, &window->player);
		dda_init(window, img);
		mlx_put_image_to_window(window->mlx, window->win, img->img, 0, 0);
		i = 1;
	}
}
