/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:41:57 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/10 19:42:58 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)// best way to put pixel in a display (using image)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_data *img, int x_start, int y_start, int size, int color)
{
	int x, y;

	for (y = y_start; y < y_start + size; y++)
	{
		for (x = x_start; x < x_start + size; x++)
			my_mlx_pixel_put(img, x, y, color);
	}
}
// 0xa71e34 hada 3jbni
// 0x1a1415 background
// replace that later 0x2e2022
void	draw_background(t_data *img, t_player *player)
{
	int	camera_height;
	int	pitch = 0; // Adjust pitch as needed

	// Calculate camera height based on the middle of the screen and pitch
	camera_height = (WINDOW_HEIGHT / 2) - (pitch * 5); // Adjust multiplier for fine-tuning

	// Ensure camera height stays within valid bounds
	if (camera_height < 0)
		camera_height = 0;
	if (camera_height > WINDOW_HEIGHT)
		camera_height = WINDOW_HEIGHT;
	// Draw sky (above the horizon)
	int sky_color = img->r_c << 16 | img->g_c << 8 | img->b_c;
	for (int i = 0; i < camera_height; i += COL_S)
	{
		for (int j = 0; j < WINDOW_WIDTH; j += COL_S)
		{
			draw_square(img, j, i, COL_S, sky_color);
		}
	}

	// Draw ground (below the horizon)
	int ground_color = img->r_f << 16 | img->g_f << 8 | img->b_f;
	for (int i = camera_height; i < WINDOW_HEIGHT; i += COL_S)
	{
		for (int j = 0; j < WINDOW_WIDTH; j += COL_S)
		{
			draw_square(img, j, i, COL_S, ground_color);
		}
	}

}

t_ray	horizontal_line(t_window *window, float dir, t_data *img)
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
	t_ray	h_line;
	int		dov = DOV;

	if (dir == 0 || dir == 180)
	{
		h_line.dist = INT_MAX;
		return (h_line);
	}

	if (dir > 0 && dir < 180)
		y = floor(window->player.y / COL_S) * COL_S + COL_S;
	else
		y = floor(window->player.y / COL_S) * COL_S - 0.0001;
	x = window->player.x + (y - window->player.y) / tan(degree_to_radian(dir));
	y_step = COL_S;
	if (dir > 180 && dir < 360)
		y_step *= -1;
	x_step = COL_S / tan(degree_to_radian(dir));
	if ((dir > 90 || dir < 270) && x_step > 0)
		x_step *= -1;
	if ((dir < 90 || dir > 270) && x_step < 0)
		x_step *= -1;
	while (dov--)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			if ((int)(y / COL_S) >= 0 && (int)(y / COL_S) < img->nb_rows && (int)(x / COL_S) >= 0 && (int)(x / COL_S) < img->nb_cols && img->map[(int)(y / COL_S)][(int)(x / COL_S)] == '1')
			{
				// draw_line(&window->img, window->player.x, window->player.y, x, y, RED);
				h_line.x = x;
				h_line.y = y;
				h_line.type = HOR;
				h_line.hit = 1;
				h_line.dist = sqrt((x - window->player.x) * (x - window->player.x) + (y - window->player.y) * (y - window->player.y));
				// h_line.dist = h_line.dist * cos(degree_to_radian(window->player.dir - dir));
				return (h_line);
			}
		}
		x += x_step;
		y += y_step;
	}
	h_line.x = x;
	h_line.y = y;
	h_line.type = HOR;
	h_line.hit = 0;
	h_line.dist = sqrt((x - window->player.x) * (x - window->player.x) + (y - window->player.y) * (y - window->player.y));
	// h_line.dist = h_line.dist * cos(degree_to_radian(window->player.dir - dir));
	return (h_line);
}

t_ray	vertical_line(t_window *window, float dir, t_data *img)
{
	double	x;
	double	y;
	double	x_steps;
	double	y_steps;
	t_ray	v_line;
	int		dov = DOV;

	if (dir == 90 || dir == 270)
	{
		v_line.dist = INT_MAX;
		return (v_line);
	}

	if (dir > 90 && dir < 270)
		x = floor(window->player.x / COL_S) * COL_S - 0.0001;
	else
		x = floor(window->player.x / COL_S) * COL_S + COL_S;
	y = window->player.y + (x - window->player.x) * tan(degree_to_radian(dir));
	x_steps = COL_S;
	if (dir > 90 && dir < 270)
		x_steps *= -1;
	y_steps = x_steps * tan(degree_to_radian(dir));

	while (dov--)
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			if ((int)(y / COL_S) >= 0 && (int)(y / COL_S) < img->nb_rows && (int)(x / COL_S) >= 0 && (int)(x / COL_S) < img->nb_cols && img->map[(int)(y / COL_S)][(int)(x / COL_S)] == '1')
			{
				v_line.x = x;
				v_line.y = y;
				v_line.type = VER;
				v_line.hit = 1;
				v_line.dist = sqrt((x - window->player.x) * (x - window->player.x) + (y - window->player.y) * (y - window->player.y));
				// v_line.dist = v_line.dist * cos(degree_to_radian(window->player.dir - dir));
				// draw_line(&window->img, window->player.x, window->player.y, x, y, GREEN);
				return (v_line);
			}
		}
		x += x_steps;
		y += y_steps;
	}
	v_line.x = x;
	v_line.y = y;
	v_line.type = VER;
	v_line.hit = 0;
	v_line.dist = sqrt((x - window->player.x) * (x - window->player.x) + (y - window->player.y) * (y - window->player.y));
	// v_line.dist = v_line.dist * cos(degree_to_radian(window->player.dir - dir));
	return (v_line);
}
int get_pixel(t_tex *tex, int x, int y)
{
    // Ensure coordinates are within bounds
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return 0; // Return black if out of bounds

    // Calculate the byte offset
    char *data = tex->addr;
    int offset = (y * tex->line_length) + (x * (tex->bits_per_pixel / 8));
    unsigned int color = *(unsigned int *)(data + offset);

    // Optional: Transparency check
    if (color == 0xFF00FF) // Assuming 0xFF00FF is your transparency color
        return -1;

    return (int)color;
}
void draw_3D(t_window *window, t_data *img, int i)
{
    int screen_height = WINDOW_HEIGHT;
    double dist = window->f_line[i].dist < 0.0001 ? 0.0001 : window->f_line[i].dist; // Avoid division by zero
    int wall_height = (int)((COL_S * D_PLAN) / dist); // Cast to int for pixel alignment
    int wall_top = (screen_height / 2) - (wall_height / 2);
    int wall_bottom = (screen_height / 2) + (wall_height / 2);

    t_tex *tex;
    double wall_x;

    // Texture selection and wall_x calculation
    if (window->f_line[i].type == HOR)
    {
        wall_x = fmod(window->f_line[i].x, COL_S) / COL_S; // Horizontal hit x offset
        tex = (window->f_line[i].y > window->player.y) ? &img->south : &img->north;
    }
    else
    {
        wall_x = fmod(window->f_line[i].y, COL_S) / COL_S; // Vertical hit y offset
        tex = (window->f_line[i].x > window->player.x) ? &img->east : &img->west;
    }

    // Clamp wall_x to avoid out-of-bounds
    if (wall_x < 0) wall_x = 0;
    if (wall_x >= 1) wall_x = 0.999;

    // Map wall_x to texture width
    int tex_x = (int)(wall_x * (tex->width - 1));
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;

    // Draw vertical strip
    for (int y = wall_top; y < wall_bottom; y++)
    {
        if (y >= 0 && y < screen_height && window->f_line[i].hit)
        {
            double tex_y = ((double)(y - wall_top) / wall_height) * (tex->height - 1);
            if (tex_y < 0) tex_y = 0;
            if (tex_y >= tex->height) tex_y = tex->height - 1;

            // Get pixel color from texture
            int color = get_pixel(tex, tex_x, (int)tex_y);
            if (color != -1) // Skip transparent pixels
                my_mlx_pixel_put(img, i, y, color);
        }
    }
}


void dda_init(t_window *window, t_data *img)
{
    float j = window->player.dir - (FOV / 2.0); // Starting ray angle
    int ray_num = WINDOW_WIDTH; // One ray per screen column
    float degree = (float)FOV / (ray_num - 1); // Fine angle step

    for (int i = 0; i < ray_num; i++)
    {
        float ray_angle = j;
        if (ray_angle < 0) ray_angle += 360;
        if (ray_angle >= 360) ray_angle -= 360;

        window->h_line[i] = horizontal_line(window, ray_angle, img);
        window->v_line[i] = vertical_line(window, ray_angle, img);

        // Choose the closer intersection
        if (window->v_line[i].dist <= window->h_line[i].dist)
        {
            window->f_line[i] = window->v_line[i];
        }
        else
        {
            window->f_line[i] = window->h_line[i];
        }

        // Correct fish-eye effect
        window->f_line[i].dist = window->f_line[i].dist * cos(degree_to_radian(window->player.dir - ray_angle));

        // Render
        if (DEBUG)
            draw_line(img, window->player.x, window->player.y, window->f_line[i].x, window->f_line[i].y, RED);
        else
            draw_3D(window, img, i);

        j += degree; // Increment ray angle
    }
    if (DEBUG)
        draw_square(img, window->player.x, window->player.y, 3, BOCCHI);
}

void	draw_walls(t_data *img)
{

	// for (int i = 0; i <= WINDOW_HEIGHT / 64; i++)
	// {
	// 	for (int j = 0; j <= WINDOW_WIDTH/64; j++)
	// 	{
	// 		draw_square(img, j * (64), i * (64), 64, );
	// 	}
	// }
	printf("rows : %d\n",img->nb_rows);
	printf("cols : %d\n",img->nb_cols);
	for (int i = 0; i < img->nb_rows; i++)
	{
		for (int j = 0; j < img->nb_cols; j++)
		{
			if (img->map[i][j] == '1')
				draw_square(img, j * (64), i * (64), 64, BLUE);
		}
	}
}

void	draw_scene(t_data *img, t_window *window)//clean the last image and redrawing evreything
{
	static int i;
	// struct timeval current_time;
	// gettimeofday(&current_time, NULL);
	// double elapsed_time = (current_time.tv_sec - window->last_time.tv_sec) + (current_time.tv_usec - window->last_time.tv_usec) / 1000000.0;
	// window->last_time = current_time;
	// printf("FPS: %f\n", 1 / elapsed_time);

	if (window->mov.r_right || window->mov.r_left || window->mov.up || window->mov.down || window->mov.left || window->mov.right || !i)
	{
		window->mov.moved = 0;
		if (window->img.img && i)
			mlx_destroy_image(window->mlx, window->img.img);
		if(DEBUG)
		{
			mlx_destroy_image(window->mlx, img->img);
			img->img = mlx_new_image(window->mlx, 1920, 1080);
			img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
			window->img.img = img->img;
			window->img.addr = img->addr;
			window->image = img;
		}
		window->img.img = mlx_new_image(window->mlx, 1920, 1080);
		window->img.addr = mlx_get_data_addr(window->img.img, &window->img.bits_per_pixel, \
			&window->img.line_length, &window->img.endian);
		if (DEBUG)
			draw_walls(img);
		else
			draw_background(img, &window->player);
		dda_init(window, img);
		mlx_put_image_to_window(window->mlx, window->win, img->img, 0, 0);
		i = 1;
	}
}
