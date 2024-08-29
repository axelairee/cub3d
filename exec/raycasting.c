/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:41:52 by abolea            #+#    #+#             */
/*   Updated: 2024/08/29 13:03:08 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	raycasting(t_cam *cam, int x)
{
	cam->wall_dist = 0;
	cam->cam_x = 2 * x / (double)SCREEN_W - 1;
	cam->ray_dir_x = cam->dir_x + cam->plane_x * cam->cam_x;
	cam->ray_dir_y = cam->dir_y + cam->plane_y * cam->cam_x;
	cam->map_x = (int)cam->pos_x;
	cam->map_y = (int)cam->pos_y;
	cam->delta_dist_x = fabs(1 / cam->ray_dir_x);
	cam->delta_dist_y = fabs(1 / cam->ray_dir_y);
	dir_ray_map(cam);
	use_dda(cam);
	wall_height(cam);
}

void	dir_ray_map(t_cam *cam)
{
	if (cam->ray_dir_x < 0)
	{
		cam->step_x = -1;
		cam->side_dist_x = (cam->pos_x - cam->map_x) * cam->delta_dist_x;
	}
	else
	{
		cam->step_x = 1;
		cam->side_dist_x = (cam->map_x + 1.0 - cam->pos_x) * cam->delta_dist_x;
	}
	if (cam->ray_dir_y < 0)
	{
		cam->step_y = -1;
		cam->side_dist_y = (cam->pos_y - cam->map_y) * cam->delta_dist_y;
	}
	else
	{
		cam->step_y = 1;
		cam->side_dist_y = (cam->map_y + 1.0 - cam->pos_y) * cam->delta_dist_y;
	}
}

void	use_dda(t_cam *cam)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cam->side_dist_x < cam->side_dist_y)
		{
			cam->side_dist_x += cam->delta_dist_x;
			cam->map_x += cam->step_x;
			cam->side = 0;
		}
		else
		{
			cam->side_dist_y += cam->delta_dist_y;
			cam->map_y += cam->step_y;
			cam->side = 1;
		}
		if (cam->map[cam->map_y][cam->map_x] > '0')
			hit = 1;
	}
}

void	wall_height(t_cam *cam)
{
	if (cam->side == 0)
		cam->wall_dist = ((double)cam->map_x - cam->pos_x \
			+ (1 - (double)cam->step_x) / 2) / cam->ray_dir_x;
	else
		cam->wall_dist = ((double)cam->map_y - cam->pos_y \
			+ (1 - (double)cam->step_y) / 2) / cam->ray_dir_y;
	cam->line_height = (int)(SCREEN_H / cam->wall_dist);
	cam->draw_start = -cam->line_height / 2 + SCREEN_H / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + SCREEN_H / 2;
	if (cam->draw_end >= SCREEN_H || cam->draw_end < 0)
		cam->draw_end = SCREEN_H - 1;
	if (cam->side == 0)
		cam->wall_x = cam->pos_y + cam->wall_dist * cam->ray_dir_y;
	else
		cam->wall_x = cam->pos_x + cam->wall_dist * cam->ray_dir_x;
	cam->wall_x -= floor(cam->wall_x);
}
