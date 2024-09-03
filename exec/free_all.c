/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:06 by abolea            #+#    #+#             */
/*   Updated: 2024/09/03 13:54:26 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_ptr(t_img *img, void *mlx_ptr)
{
	if (img)
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
}

void	free_images(t_img *img, void *mlx_ptr)
{
	free_ptr(img, mlx_ptr);
	if (img->north)
	{
		free(img->north);
		img->north = NULL;
	}
	if (img->south)
	{
		free(img->south);
		img->south = NULL;
	}
	if (img->east)
	{
		free(img->east);
		img->east = NULL;
	}
	if (img->west)
	{
		free(img->west);
		img->west = NULL;
	}
}

void	free_all(t_mlx *mlx, t_cam *cam)
{
	if (mlx)
	{
		if (mlx->win_ptr)
		{
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
			mlx->win_ptr = NULL;
		}
		if (mlx->img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		if (cam)
			free_images(&mlx->img, mlx->mlx_ptr);
		if (mlx->mlx_ptr)
		{
			mlx_destroy_display(mlx->mlx_ptr);
			free(mlx->mlx_ptr);
		}
	}
	if (cam)
		free(cam);
}

int	handle_exit(t_mlx *mlx)
{
	free_all(mlx, mlx->cam);
	free_cube(&mlx->cub);
	exit(0);
	return (0);
}
