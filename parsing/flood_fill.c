/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:34:44 by lle-pier          #+#    #+#             */
/*   Updated: 2024/07/30 15:58:30 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill(t_cub *data, int x, int y)
{
	if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_width \
	|| data->map[x][y] == ' ' || !data->map[x][y])
	{
		return ;
	}
	if (data->map[x][y] == '1' || data->map[x][y] == 'V')
		return ;
	if (data->map[x][y] == '0')
		data->map[x][y] = 'V';
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y -1);
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
}

int	unflood_fill(t_cub *data, int x, int y)
{
	if (x < 0 || x >= data->map_height || y < 0 || y >= data->map_width \
	|| data->map[x][y] == ' ' || !data->map[x][y])
	{
		return (-1);
	}
	if (data->map[x][y] == '1' || data->map[x][y] == '0')
		return (0);
	if (data->map[x][y] == 'V')
	{
		data->map[x][y] = '0';
	}
	if (unflood_fill(data, x, y + 1) == -1)
		return (-1);
	if (unflood_fill(data, x, y -1) == -1)
		return (-1);
	if (unflood_fill(data, x + 1, y) == -1)
		return (-1);
	if (unflood_fill(data, x - 1, y) == -1)
		return (-1);
	return (0);
}

int	is_map_close(t_cub *c)
{
	flood_fill(c, c->player.x, c->player.y);
	if (unflood_fill(c, c->player.x, c->player.y) == -1)
		return (print_cube(c), printf("map not closed !!!\n"), -1);
	return (0);
}

