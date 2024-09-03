/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:43:08 by abolea            #+#    #+#             */
/*   Updated: 2024/09/03 12:45:30 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_key_press(int keycode, void *param)
{
	t_mlx	*mlx;
	t_cam	*cam;

	mlx = (t_mlx *)param;
	cam = mlx->cam;
	if (keycode == 65307)
		handle_exit(mlx);
	else if (keycode == 119)
		cam->keys.w = 1;
	else if (keycode == 115)
		cam->keys.s = 1;
	else if (keycode == 97)
		cam->keys.a = 1;
	else if (keycode == 100)
		cam->keys.d = 1;
	else if (keycode == 65361)
		cam->keys.fg = 1;
	else if (keycode == 65363)
		cam->keys.fd = 1;
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_mlx	*mlx;
	t_cam	*cam;

	mlx = (t_mlx *)param;
	cam = mlx->cam;
	if (keycode == 119)
		cam->keys.w = 0;
	else if (keycode == 115)
		cam->keys.s = 0;
	else if (keycode == 97)
		cam->keys.a = 0;
	else if (keycode == 100)
		cam->keys.d = 0;
	else if (keycode == 65361)
		cam->keys.fg = 0;
	else if (keycode == 65363)
		cam->keys.fd = 0;
	return (0);
}

int	update_position(t_mlx *mlx)
{
	t_cam	*cam;

	cam = mlx->cam;
	if (cam->keys.w)
		move_forward(cam, cam->map);
	if (cam->keys.s)
		move_backward(cam, cam->map);
	if (cam->keys.a)
		move_left(cam, cam->map);
	if (cam->keys.d)
		move_right(cam, cam->map);
	if (cam->keys.fg)
		rotate_left(cam);
	if (cam->keys.fd)
		rotate_right(cam);
	put_wall(cam, &mlx->img);
	color_floor_and_ceiling(&mlx->img, cam);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return (0);
}

void free_images(t_img *img, void *mlx_ptr)
{
	if (img->north && img->north->tex_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->north->tex_ptr);
		img->north->tex_ptr = NULL;
	}
	if (img->south && img->south->tex_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->south->tex_ptr);
		img->south->tex_ptr = NULL;
	}
	if (img->east && img->east->tex_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->east->tex_ptr);
		img->east->tex_ptr = NULL;
	}
	if (img->west && img->west->tex_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->west->tex_ptr);
		img->west->tex_ptr = NULL;
	}
}

void free_ptr(t_img *img, void *mlx_ptr)
{
	if (img->img_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
	if (img->img_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
	free(img->north);
	free(img->south);
	free(img->east);
	free(img->west);
}

void	free_all(t_mlx *mlx, t_cam *cam)
{
	if (mlx->win_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	free_images(&mlx->img, mlx->mlx_ptr);
	free_ptr(&mlx->img, mlx->mlx_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
	}
	if (cam)
		free(cam);
}


int	handle_exit(t_mlx *mlx)
{
	free_all(mlx, mlx->cam);
	exit(0);
	return (0);
}
