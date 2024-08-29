/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:37:24 by marvin            #+#    #+#             */
/*   Updated: 2024/07/18 11:37:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_north_and_south(t_cub *cub, t_cam *cam)
{
	if (cub->player.direction == 'N')
	{
		cam->dir_x = 0;
		cam->dir_y = -1;
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
	else if (cub->player.direction == 'S')
	{
		cam->dir_x = 0;
		cam->dir_y = 1;
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
}

void	get_player_dir(t_cub *cub, t_cam *cam)
{
	get_north_and_south(cub, cam);
	if (cub->player.direction == 'E')
	{
		cam->dir_x = 1;
		cam->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = -0.66;
	}
	else if (cub->player.direction == 'W')
	{
		cam->dir_x = -1;
		cam->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
}

void	get_floor_and_ceiling_color(t_cam *cam, t_cub *cub)
{
	cam->c_r = cub->r_ceiling;
	cam->c_g = cub->g_ceiling;
	cam->c_b = cub->b_ceiling;
	cam->f_r = cub->r_floor;
	cam->f_g = cub->g_floor;
	cam->f_b = cub->b_floor;
	cam->c_color = rgb_to_hex(cam->c_r, cam->c_g, cam->c_b);
	cam->f_color = rgb_to_hex(cam->f_r, cam->f_g, cam->f_b);
}

t_cam	*init_argument(t_cub *cub)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
	{
		free(cam);
		exit(1);
	}
	cam->map = cub->map;
	cam->pos_y = cub->player.x + 0.5;
	cam->pos_x = cub->player.y + 0.5;
	get_floor_and_ceiling_color(cam, cub);
	get_player_dir(cub, cam);
	cam->draw_start = 0;
	cam->is_open = 0;
	cam->draw_end = SCREEN_H;
	cam->line_height = SCREEN_H;
	return (cam);
}

int	init_textures(t_mlx *mlx, t_cub *cub)
{
	mlx->img.north = malloc(sizeof(t_img));
	if (!mlx->img.north)
		return (-1);
	mlx->img.south = malloc(sizeof(t_img));
	if (!mlx->img.north)
		return (-1);
	mlx->img.east = malloc(sizeof(t_img));
	if (!mlx->img.north)
		return (-1);
	mlx->img.west = malloc(sizeof(t_img));
	if (!mlx->img.north)
		return (-1);
	if (!mlx->img.north || !mlx->img.south || !mlx->img.east || !mlx->img.west)
		return (-1);
	if (load_textures(mlx->img.north, mlx, cub->no) == -1)
		return (-1);
	if (load_textures(mlx->img.south, mlx, cub->so) == -1)
		return (-1);
	if (load_textures(mlx->img.east, mlx, cub->ea) == -1)
		return (-1);
	if (load_textures(mlx->img.west, mlx, cub->we) == -1)
		return (-1);
	return (0);
}
