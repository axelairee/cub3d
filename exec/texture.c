/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:06:20 by abolea            #+#    #+#             */
/*   Updated: 2024/08/29 13:57:08 by abolea           ###   ########.fr       */
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

void	create_image(t_img *img, t_mlx *mlx)
{
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H);
	if (!img->img_ptr)
		return ;
	img->data = mlx_get_data_addr(img->img_ptr, \
	&img->bpp, &img->line_length, &img->endian);
}
