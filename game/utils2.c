/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:06:21 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/22 15:41:58 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_wall_collision(double x, double y, t_data *img)
{
	return ((int)(y / COL_S) >= 0 && (int)(y / COL_S) < img->nb_rows
		&& (int)(x / COL_S) >= 0 && (int)(x / COL_S) < img->nb_cols
		&& img->map[(int)(y / COL_S)][(int)(x / COL_S)] == '1');
}

void	init_horizontal_steps(double *x_step, double *y_step, float dir)
{
	*y_step = COL_S;
	if (dir > 180 && dir < 360)
		*y_step *= -1;
	*x_step = COL_S / tan(degree_to_radian(dir));
	if ((dir > 90 || dir < 270) && *x_step > 0)
		*x_step *= -1;
	if ((dir < 90 || dir > 270) && *x_step < 0)
		*x_step *= -1;
}

t_ray	handle_hor_wall_hit(double x, double y, t_window *window, t_data *img)
{
	t_ray	h_line;

	h_line.x = x;
	h_line.y = y;
	h_line.type = HOR;
	h_line.hit = 1;
	h_line.dist = sqrt((x - window->player.x) * (x - window->player.x)
			+ (y - window->player.y) * (y - window->player.y));
	return (h_line);
}

t_ray	handle_hor_no_hit(double x, double y, t_window *window)
{
	t_ray	h_line;

	h_line.x = x;
	h_line.y = y;
	h_line.type = HOR;
	h_line.hit = 0;
	h_line.dist = sqrt((x - window->player.x) * (x - window->player.x)
			+ (y - window->player.y) * (y - window->player.y));
	return (h_line);
}

t_ray	horizontal_line(t_window *window, float dir, t_data *img)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	int		dov;

	dov = DOV;
	if (dir == 0 || dir == 180)
		return ((t_ray){.dist = INT_MAX});
	y = floor(window->player.y / COL_S) * COL_S;
	if (dir > 0 && dir < 180)
		y += COL_S;
	else
		y += -0.0001;
	x = window->player.x + (y - window->player.y) / tan(degree_to_radian(dir));
	init_horizontal_steps(&x_step, &y_step, dir);
	while (dov--)
	{
		if (check_wall_collision(x, y, img))
			return (handle_hor_wall_hit(x, y, window, img));
		x += x_step;
		y += y_step;
	}
	return (handle_hor_no_hit(x, y, window));
}
