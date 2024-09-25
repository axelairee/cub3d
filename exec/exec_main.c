/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:06:52 by abolea            #+#    #+#             */
/*   Updated: 2024/09/25 16:53:14 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_texture(t_cub *cub, t_mlx *mlx, t_cam *cam)
{
	int	res;

	res = init_textures(mlx, cub);
	if (res == -1)
	{
		free_all(mlx, cam, 3);
		return (-1);
	}
	else if (res == -2)
	{
		free_all(mlx, cam, 2);
		return (-1);
	}
	else if (res == -3)
	{
		free_all(mlx, cam, 4);
		return (-1);
	}
	else if (res == -4)
	{
		free_all(mlx, cam, 5);
		return (-1);
	}
	return (0);
}

int	exec_main(t_cub *cub)
{
	t_mlx	mlx;
	t_cam	*cam;

	if (init_mlx(&mlx, cub) == -1)
		return (-2);
	cam = init_argument(cub);
	if (!cam)
	{
		free_all(&mlx, NULL, 2);
		return (-2);
	}
	mlx.cam = cam;
	if (check_texture(cub, &mlx, cam) == -1)
		return (-2);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L << 1, handle_key_release, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 17, handle_exit, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, update_position, &mlx);
	mlx_loop(mlx.mlx_ptr);
	free_all(&mlx, cam, 1);
	return (0);
}
