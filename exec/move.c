/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:44:01 by abolea            #+#    #+#             */
/*   Updated: 2024/08/29 13:16:19 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_cam *cam, char **map)
{
	double	movespeed;
	double	new_pos_x;
	double	new_pos_y;
	int		map_x;
	int		map_y;

	movespeed = 0.05;
	new_pos_x = cam->pos_x + cam->dir_x * movespeed;
	new_pos_y = cam->pos_y + cam->dir_y * movespeed;
	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;
	if (map[map_y][map_x] == '0')
	{
		cam->pos_x = new_pos_x;
		cam->pos_y = new_pos_y;
	}
}

void	move_backward(t_cam *cam, char **map)
{
	double	movespeed;
	double	new_pos_x;
	double	new_pos_y;
	int		map_x;
	int		map_y;

	movespeed = 0.05;
	new_pos_x = cam->pos_x - cam->dir_x * movespeed;
	new_pos_y = cam->pos_y - cam->dir_y * movespeed;
	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;
	if (map[map_y][map_x] == '0')
	{
		cam->pos_x = new_pos_x;
		cam->pos_y = new_pos_y;
	}
}

void	move_left(t_cam *cam, char **map)
{
	double	movespeed;
	double	new_pos_x;
	double	new_pos_y;
	int		map_x;
	int		map_y;	

	movespeed = 0.05;
	new_pos_x = cam->pos_x - cam->dir_y * movespeed;
	new_pos_y = cam->pos_y + cam->dir_x * movespeed;
	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;
	if (map[map_y][map_x] == '0')
	{
		cam->pos_x = new_pos_x;
		cam->pos_y = new_pos_y;
	}
}

void	move_right(t_cam *cam, char **map)
{
	double	movespeed;
	double	new_pos_x;
	double	new_pos_y;
	int		map_x;
	int		map_y;	

	movespeed = 0.05;
	new_pos_x = cam->pos_x + cam->dir_y * movespeed;
	new_pos_y = cam->pos_y - cam->dir_x * movespeed;
	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;
	if (map[map_y][map_x] == '0')
	{
		cam->pos_x = new_pos_x;
		cam->pos_y = new_pos_y;
	}
}
