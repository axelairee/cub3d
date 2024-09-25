/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:41:34 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/25 11:56:30 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_line(const char *line)
{
	if (line[0] == '\0' || ft_strncmp(line, "NO", 2) == 0 \
	|| ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
	|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "F ", 2) == 0 \
	|| ft_strncmp(line, "C ", 2) == 0 || (line[0] == '\n' && line[1] == '\0'))
	{
		return (1);
	}
	return (0);
}

int	is_valid_map(const char *line)
{
	if (line[0] == '\0' || line[0] == '\n')
		return (0);
	if (line[0] == ' ')
	{
		while (*line == ' ')
			line++;
		if (*line == '\0' || *line == '\n')
			return (0);
	}
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != '2' && *line != 'N' \
		&& *line != 'S' && *line != 'E' && *line != 'W' && *line != ' ' \
		&& *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
