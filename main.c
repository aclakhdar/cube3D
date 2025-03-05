/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:07:31 by aclakhda          #+#    #+#             */
/*   Updated: 2025/03/05 19:29:47 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
void	set_dir_angle(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'N')
		data->player.rotation_angle = 90;
	if (data->map[y][x] == 'S')
		data->player.rotation_angle = 270;
	if (data->map[y][x] == 'W')
		data->player.rotation_angle = 0;
	if (data->map[y][x] == 'E')
		data->player.rotation_angle = 180;
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
	img->texture[TEX_EAST] = load_texture(img->mlx_ptr, img->ea,
			&(img->texture_width), &(img->texture_height));
	img->texture[TEX_NORTH] = load_texture(img->mlx_ptr, img->no,
			&(img->texture_width), &(img->texture_height));
	img->texture[TEX_SOUTH] = load_texture(img->mlx_ptr, img->we,
			&(img->texture_width), &(img->texture_height));
	img->texture[TEX_WEST] = load_texture(img->mlx_ptr, img->so,
			&(img->texture_width), &(img->texture_height));
	// img->gun_texture = load_texture(img->mlx_ptr, "coolgun.xpm",
	// 		&(img->gun_texture_width), &(img->gun_texture_height));
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
	printf("pos : %f",img.player.x);
	printf("pos2 : %f",img.player.y);
	load_textures(&img);
	game(&img);
	return (0);
}
