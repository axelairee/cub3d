/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:06:20 by abolea            #+#    #+#             */
/*   Updated: 2024/09/25 16:51:13 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_textures(t_img *img, t_mlx *mlx, char *filename)
{
	img->tex_width = 0;
	img->tex_height = 0;
	img->tex_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
	filename, &img->tex_width, &img->tex_height);
	if (!img->tex_ptr)
		return (-1);
	img->tex_data = mlx_get_data_addr(img->tex_ptr, \
	&img->tex_bpp, &img->tex_line_length, &img->tex_endian);
	if (!img->tex_data)
		return (-1);
	return (0);
}

void	put_wall(t_cam *cam, t_img *img)
{
	int	x;

	x = 0;
	while (x < SCREEN_W)
	{
		raycasting(cam, x);
		draw_column(cam, img, x);
		x++;
	}
}

int	create_image(t_img *img, t_mlx *mlx)
{
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!img->img_ptr)
		return (-1);
	img->data = mlx_get_data_addr(img->img_ptr, \
	&img->bpp, &img->line_length, &img->endian);
	if (!img->data)
		return (-1);
	return (0);
}

int	init_textures(t_mlx *mlx, t_cub *cub)
{
	mlx->img.north = malloc(sizeof(t_img));
	if (!mlx->img.north)
		return (-2);
	mlx->img.south = malloc(sizeof(t_img));
	if (!mlx->img.south)
		return (-2);
	mlx->img.east = malloc(sizeof(t_img));
	if (!mlx->img.east)
		return (-2);
	mlx->img.west = malloc(sizeof(t_img));
	if (!mlx->img.west)
		return (-2);
	if (!mlx->img.north || !mlx->img.south || !mlx->img.east || !mlx->img.west)
		return (-2);
	if (load_textures(mlx->img.north, mlx, cub->no) == -1)
		return (-2);
	if (load_textures(mlx->img.south, mlx, cub->so) == -1)
		return (-1);
	if (load_textures(mlx->img.east, mlx, cub->ea) == -1)
		return (-3);
	if (load_textures(mlx->img.west, mlx, cub->we) == -1)
		return (-4);
	return (0);
}
