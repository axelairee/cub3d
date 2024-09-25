/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:44:01 by abolea            #+#    #+#             */
/*   Updated: 2024/09/25 12:33:48 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_cam *cam, char **map)
{
	double	movespeed;
	double	new_pos_x;
	double	new_pos_y;
	double	hitbox;

	movespeed = 0.05;
	hitbox = 0.1;
	new_pos_x = cam->pos_x + cam->dir_x * movespeed;
	new_pos_y = cam->pos_y + cam->dir_y * movespeed;
	if (map[(int)(cam->pos_y)][(int)(new_pos_x + cam->dir_x * hitbox)] == '0' &&
		map[(int)(new_pos_y + cam->dir_y * hitbox)][(int)(cam->pos_x)] == '0')
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
	double	hitbox;

	movespeed = 0.05;
	hitbox = 0.1;
	new_pos_x = cam->pos_x - cam->dir_x * movespeed;
	new_pos_y = cam->pos_y - cam->dir_y * movespeed;
	if (map[(int)(cam->pos_y)][(int)(new_pos_x - cam->dir_x * hitbox)] == '0' &&
		map[(int)(new_pos_y - cam->dir_y * hitbox)][(int)(cam->pos_x)] == '0')
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
	double	hitbox;

	movespeed = 0.05;
	hitbox = 0.1;
	new_pos_x = cam->pos_x - cam->dir_y * movespeed;
	new_pos_y = cam->pos_y + cam->dir_x * movespeed;
	if (map[(int)(cam->pos_y)][(int)(new_pos_x - cam->dir_y * hitbox)] == '0' &&
		map[(int)(new_pos_y + cam->dir_x * hitbox)][(int)(cam->pos_x)] == '0')
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
	double	hitbox;

	movespeed = 0.05;
	hitbox = 0.1;
	new_pos_x = cam->pos_x + cam->dir_y * movespeed;
	new_pos_y = cam->pos_y - cam->dir_x * movespeed;
	if (map[(int)(cam->pos_y)][(int)(new_pos_x + cam->dir_y * hitbox)] == '0' &&
		map[(int)(new_pos_y - cam->dir_x * hitbox)][(int)(cam->pos_x)] == '0')
	{
		cam->pos_x = new_pos_x;
		cam->pos_y = new_pos_y;
	}
}
