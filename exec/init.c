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
		cam->dir_y = -1.01;
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
	else if (cub->player.direction == 'S')
	{
		cam->dir_x = 0;
		cam->dir_y = 1.01;
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
}

void	get_player_dir(t_cub *cub, t_cam *cam)
{
	get_north_and_south(cub, cam);
	if (cub->player.direction == 'E')
	{
		cam->dir_x = 1.01;
		cam->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
	else if (cub->player.direction == 'W')
	{
		cam->dir_x = -1.01;
		cam->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = -0.66;
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
		return (NULL);
	cam->map = cub->map;
	cam->pos_y = cub->player.x + 0.5;
	cam->pos_x = cub->player.y + 0.5;
	get_floor_and_ceiling_color(cam, cub);
	get_player_dir(cub, cam);
	cam->draw_start = 0;
	cam->is_open = 0;
	cam->draw_end = SCREEN_H;
	cam->line_height = SCREEN_H;
	cam->keys.w = 0;
	cam->keys.s = 0;
	cam->keys.a = 0;
	cam->keys.d = 0;
	cam->keys.fg = 0;
	cam->keys.fd = 0;
	return (cam);
}

int	init_mlx(t_mlx *mlx, t_cub *cub)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (-1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "Cub3D");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (-1);
	}
	if (create_image(&mlx->img, mlx) == -1)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (-1);
	}
	mlx->img.north = NULL;
	mlx->img.east = NULL;
	mlx->img.south = NULL;
	mlx->img.west = NULL;
	mlx->cub = cub;
	return (0);
}
