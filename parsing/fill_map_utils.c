/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:49:30 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/24 16:30:59 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	compare_strings(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (0);
		}
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
	{
		return (1);
	}
	return (0);
}

int	compare_textures(t_cub *cub)
{
	if (compare_strings(cub->ea, cub->no) || compare_strings(cub->ea, cub->so) \
	|| compare_strings(cub->we, cub->ea) || compare_strings(cub->so, cub->we) \
	|| compare_strings(cub->no, cub->so) || compare_strings(cub->no, cub->we))
		return (print_error("Error: textures are the same\n"), 1);
	return (0);
}

void	count_dimensions(t_cub *cub)
{
	int	i;

	i = 0;
	cub->map_height = 0;
	cub->map_width = 0;
	while (cub->map[i])
	{
		if (ft_strlen(cub->map[i]) > cub->map_width)
			cub->map_width = ft_strlen(cub->map[i]);
		cub->map_height++;
		i++;
	}
}

int	check_param_completed(t_cub *cub)
{
	if (!cub->no_state || !cub->so_state || !cub->we_state || !cub->ea_state \
	|| !cub->floor_state || !cub->ceiling_state)
		return (0);
	return (1);
}
