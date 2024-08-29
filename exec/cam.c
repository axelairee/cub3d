/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:44:11 by abolea            #+#    #+#             */
/*   Updated: 2024/08/29 13:30:15 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_cam *cam)
{
	double	rotspeed;
	double	olddrix;
	double	oldplanex;

	rotspeed = 0.04;
	olddrix = cam->dir_x;
	oldplanex = cam->plane_x;
	cam->dir_x = cam->dir_x * cos(rotspeed) - cam->dir_y * sin(rotspeed);
	cam->dir_y = olddrix * sin(rotspeed) + cam->dir_y * cos(rotspeed);
	cam->plane_x = cam->plane_x * cos(rotspeed) - cam->plane_y * sin(rotspeed);
	cam->plane_y = oldplanex * sin(rotspeed) + cam->plane_y * cos(rotspeed);
}

void	rotate_right(t_cam *cam)
{
	double	rotspeed;
	double	olddrix;
	double	oldplanex;

	rotspeed = -0.04;
	olddrix = cam->dir_x;
	oldplanex = cam->plane_x;
	cam->dir_x = cam->dir_x * cos(rotspeed) - cam->dir_y * sin(rotspeed);
	cam->dir_y = olddrix * sin(rotspeed) + cam->dir_y * cos(rotspeed);
	cam->plane_x = cam->plane_x * cos(rotspeed) - cam->plane_y * sin(rotspeed);
	cam->plane_y = oldplanex * sin(rotspeed) + cam->plane_y * cos(rotspeed);
}
