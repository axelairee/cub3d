/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:45:17 by abolea            #+#    #+#             */
/*   Updated: 2024/08/29 12:53:18 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	img->pos = y * img->line_length + x * (img->bpp / 8);
	*(int *)(img->data + img->pos) = color;
}

t_cardinal_direction	ft_get_cardinal_direction(t_cam *cam)
{
	if (cam->ray_dir_x > 0 && cam->ray_dir_y < 0)
		return (EAST);
	if (cam->ray_dir_x > 0 && cam->ray_dir_y > 0)
		return (SOUTH);
	if (cam->ray_dir_x < 0 && cam->ray_dir_y > 0)
		return (WEST);
	return (NORTH);
}

int	rgb_to_hex(int r, int g, int b)
{
	int	color;

	color = (r << 16) + (g << 8) + b;
	return (color);
}

t_img	*get_dir(t_cam *cam, t_img *img)
{
	if (cam->side == 0)
	{
		if (cam->ray_dir_x > 0)
			return (img->west);
		else
			return (img->east);
	}
	if (cam->side == 1)
	{
		if (cam->ray_dir_y > 0)
			return (img->north);
		else
			return (img->south);
	}
	return (img->north);
}
