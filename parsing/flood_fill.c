/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:34:44 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:24 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_first_and_last_line(t_cub *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (c->map[i][j])
	{
		if (c->map[i][j] != '1' && c->map[i][j] != ' ')
			return (print_error("Map is not closed\n"), -1);
		j++;
	}
	i = c->map_height - 1;
	j = 0;
	while (c->map[i][j])
	{
		if (c->map[i][j] != '1' && c->map[i][j] != ' ')
			return (print_error("Map is not closed\n"), -1);
		j++;
	}
	return (0);
}

int	check_map_closed(t_cub *c, int i, int j)
{
	if (check_first_and_last_line(c) == -1)
		return (-1);
	while (i < c->map_height - 1)
	{
		j = 1;
		while (c->map[i][j])
		{
			if (c->map[i][j] == '0')
			{
				if (ft_strlen(c->map[i + 1]) < j || \
				ft_strlen(c->map[i - 1]) < j)
					return (print_error("Map is not closed\n"), -1);
				if (c->map[i][j + 1] == ' ' || c->map[i][j - 1] == ' ' \
				|| c->map[i + 1][j] == ' ' || c->map[i - 1][j] == ' ')
					return (print_error("Map is not closed\n"), -1);
				if (c->map[i][j + 1] == '\0' || c->map[i][j - 1] == '\0' \
				|| c->map[i + 1][j] == '\0' || c->map[i - 1][j] == '\0')
					return (print_error("Map is not closed\n"), -1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
