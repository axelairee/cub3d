/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:46:38 by abolea            #+#    #+#             */
/*   Updated: 2024/09/25 11:46:33 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	color_floor_and_ceiling(t_img *img, t_cam *cam)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_W)
	{
		y = 0;
		raycasting(cam, x);
		while (y < cam->draw_start)
		{
			if (y < SCREEN_H && y > 0)
				put_pixel(img, x, y, cam->c_color);
			y++;
		}
		y = cam->draw_end;
		raycasting(cam, x);
		while (y < SCREEN_H)
		{
			if (y < SCREEN_H && y > 0)
				put_pixel(img, x, y, cam->f_color);
			y++;
		}
		x++;
	}
}

int	draw_calcul(t_cam *cam, t_img *wall_dir)
{
	int	tex_x;

	if (cam->side == 0)
		cam->wall_x = cam->pos_y + cam->wall_dist * cam->ray_dir_y;
	else
		cam->wall_x = cam->pos_x + cam->wall_dist * cam->ray_dir_x;
	cam->wall_x -= floor(cam->wall_x);
	tex_x = (int)(cam->wall_x * (double)wall_dir->tex_width);
	if (cam->side == 0 && cam->ray_dir_x < 0)
		tex_x = wall_dir->tex_width - tex_x - 1;
	if (cam->side == 1 && cam->ray_dir_y > 0)
		tex_x = wall_dir->tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_column(t_cam *cam, t_img *img, int x)
{
	int				y;
	t_img			*wall_dir;
	unsigned int	color;

	y = cam->draw_start;
	wall_dir = get_dir(cam, img);
	cam->tex_x = draw_calcul(cam, wall_dir);
	cam->step = 1.0 * wall_dir->tex_height / cam->line_height;
	cam->tex_pos = (cam->draw_start - \
	SCREEN_H / 2 + cam->line_height / 2) * cam->step;
	while (y < cam->draw_end)
	{
		cam->tex_y = (int)cam->tex_pos;
		if (cam->tex_y >= wall_dir->tex_height)
			cam->tex_y = wall_dir->tex_height - 1;
		color = *(unsigned int *)(wall_dir->tex_data + (cam->tex_y * \
		wall_dir->tex_line_length + cam->tex_x * (wall_dir->tex_bpp / 8)));
		put_pixel(img, x, y, color);
		cam->tex_pos += cam->step;
		y++;
	}
}
