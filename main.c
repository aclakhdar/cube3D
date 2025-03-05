/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclakhda <aclakhda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:07:31 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/05 20:55:29 by aclakhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_dir_angle(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'N')
		data->dir = 270;
	if (data->map[y][x] == 'S')
		data->dir = 90;
	if (data->map[y][x] == 'W')
		data->dir = 180;
	if (data->map[y][x] == 'E')
		data->dir = 0;
}

void	find_player_position(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->nb_rows)
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'W'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'S')
			{
				set_dir_angle(data, x, y);
				data->player.x = x * 64 + 64 / 2;
				data->player.y = y * 64 + 64 / 2;
				data->map[y][x] = '0';
			}
		}
	}
}
void	initialize_player(t_data *data)
{
	find_player_position(data);

}
void	*load_texture(void *mlx_ptr, char *file_name, int *width, int *height)
{
	void	*texture;

	texture = mlx_xpm_file_to_image(mlx_ptr, file_name, width, height);
	if (!texture)
	{
		printf("Failed to load texture image: %s\n", file_name);
		exit(EXIT_FAILURE);
	}
	return (texture);
}
void	load_textures(t_data *img)
{
	img->east.img = load_texture(img->mlx_ptr, img->ea,
			&(img->east.width), &(img->east.height));
	img->north.img = load_texture(img->mlx_ptr, img->no,
			&(img->north.width), &(img->north.height));
	img->south.img = load_texture(img->mlx_ptr, img->we,
			&(img->south.width), &(img->south.height));
	img->west.img = load_texture(img->mlx_ptr, img->so,
			&(img->west.width), &(img->west.height));
	// img->gun_texture = load_texture(img->mlx_ptr, "coolgun.xpm",
	// 		&(img->gun_texture_width), &(img->gun_texture_height));
	img->north.addr = mlx_get_data_addr(img->north.img, &img->north.bits_per_pixel,
										&img->north.line_length, &img->north.endian);
	img->south.addr = mlx_get_data_addr(img->south.img, &img->south.bits_per_pixel,
										&img->south.line_length, &img->south.endian);
	img->east.addr = mlx_get_data_addr(img->east.img, &img->east.bits_per_pixel,
										&img->east.line_length, &img->east.endian);
	img->west.addr = mlx_get_data_addr(img->west.img, &img->west.bits_per_pixel,
										&img->west.line_length, &img->west.endian);

}

int main(int ac, char **av)
{
	t_data	img;
	img.tilesize = 32;
	parsing(ac,av,&img);
	if (img.nb_cols > 35 || img.nb_rows > 24)
		img.tilesize = 16;
	if (img.nb_cols > 70 || img.nb_rows > 48)
		img.tilesize = 4;
	initialize_player(&img);
	game(&img);

	return (0);
}
