/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:07:55 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/11 18:35:30 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_vertical_steps(double *x_steps, double *y_steps, float dir)
{
	*x_steps = COL_S;
	if (dir > 90 && dir < 270)
		*x_steps *= -1;
	*y_steps = *x_steps * tan(degree_to_radian(dir));
}

t_ray	handle_wall_hit(double x, double y, t_window *window, t_data *img)
{
	t_ray	v_line;

	v_line.x = x;
	v_line.y = y;
	v_line.type = VER;
	v_line.hit = 1;
	v_line.dist = sqrt((x - window->player.x) * (x - window->player.x)
			+ (y - window->player.y) * (y - window->player.y));
	return (v_line);
}

t_ray	handle_no_hit(double x, double y, t_window *window)
{
	t_ray	v_line;

	v_line.x = x;
	v_line.y = y;
	v_line.type = VER;
	v_line.hit = 0;
	v_line.dist = sqrt((x - window->player.x) * (x - window->player.x)
			+ (y - window->player.y) * (y - window->player.y));
	return (v_line);
}

t_ray	vertical_line(t_window *window, float dir, t_data *img)
{
	double	x;
	double	y;
	double	x_steps;
	double	y_steps;
	int		dov;

	dov = DOV;
	if (dir == 90 || dir == 270)
		return ((t_ray){.dist = INT_MAX});
	x = floor(window->player.x / COL_S) * COL_S;
	if (dir > 90 && dir < 270)
		x += -0.0001;
	else
		x += COL_S;
	y = window->player.y + (x - window->player.x) * tan(degree_to_radian(dir));
	init_vertical_steps(&x_steps, &y_steps, dir);
	while (dov--)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			if (check_wall_collision(x, y, img))
				return (handle_wall_hit(x, y, window, img));
		x += x_steps;
		y += y_steps;
	}
	return (handle_no_hit(x, y, window));
}

int	get_pixel(t_tex *tex, int x, int y)
{
	unsigned int	color;
	int				offset;
	char			*data;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	data = tex->addr;
	offset = (y * tex->line_length) + (x * (tex->bits_per_pixel / 8));
	color = *(unsigned int *)(data + offset);
	if (color == 0xFF00FF)
		return (-1);
	return ((int)color);
}
