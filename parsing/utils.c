/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:41:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/25 12:56:28 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_buffer(void)
{
	if (BUFFER_SIZE < 1)
		return (print_error("Error: BUFFER_SIZE too small\n"), 1);
	if (BUFFER_SIZE > 10000)
		return (print_error("Error: BUFFER_SIZE too big\n"), 1);
	return (0);
}

void	print_error(const char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(2, msg, len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_cub_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strcmp(filename + len - 4, ".cub") == 0)
		return (1);
	return (0);
}

int	get_player_position(t_cub *c, int x, int y)
{
	y = 0;
	c->player.direction = 0;
	while (y < c->map_height)
	{
		x = 0;
		while (x < c->map_width && c->map[y][x])
		{
			if ((c->map[y][x] == 'S' || c->map[y][x] == 'E' || \
			c->map[y][x] == 'W' || c->map[y][x] == 'N'))
			{
				c->player.x = y;
				c->player.y = x;
				if (c->player.direction)
					return (-1);
				c->player.direction = c->map[y][x];
				c->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (!c->player.direction)
		return (print_error("Error: no player\n"), -1);
	return (0);
}
