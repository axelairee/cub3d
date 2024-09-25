/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:35:17 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/23 14:14:09 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' \
	|| c == '\f' || c == '\r' || c == '\0' || c == ',')
		return (0);
	else
		return (-1);
}

int	check_str_colors(t_cub *cub, int i, int j, int h)
{
	while (cub->ceiling[++j])
	{
		if (ft_isdigit(cub->ceiling[j]) == 1)
			h++;
		if ((cub->ceiling[j] == ',' && h > 0) || !(cub->ceiling[j] == ',' || \
		ft_isdigit(cub->ceiling[j]) == 1 || cub->ceiling[j] == ' '))
			i++;
	}
	if (i != 3)
		return (print_error("Invalid ceiling color.\n"), 1);
	i = 0;
	j = -1;
	h = 0;
	while (cub->floor[++j])
	{
		if (ft_isdigit(cub->floor[j]) == 1)
			h++;
		if ((cub->floor[j] == ',' && h > 0) || !(cub->floor[j] == ',' || \
		ft_isdigit(cub->floor[j]) == 1 || cub->floor[j] == ' '))
			i++;
	}
	if (i != 3)
		return (print_error("invalid floor color.\n"), 1);
	return (0);
}

int	string_to_int(const char *str, int *index)
{
	int	result;

	result = 0;
	while (str[*index] != '\0')
	{
		while (str[*index] == ' ')
			(*index)++;
		if (ft_isdigit(str[*index]) != 1)
			break ;
		result = result * 10 + (str[*index] - '0');
		(*index)++;
	}
	if (ft_isdigit(str[*index - 1]) == -1)
		return (-1);
	return (result);
}

int	parse_rgb(const char *rgbString, int *r, int *g, int *b)
{
	int	index;

	index = 0;
	*r = string_to_int(rgbString, &index);
	if (*r < 0)
		return (print_error("RGB values must be between 0 and 255.\n"), 1);
	if (rgbString[index] == ',')
		index++;
	*g = string_to_int(rgbString, &index);
	if (*g < 0)
		return (print_error("RGB values must be between 0 and 255.\n"), 1);
	if (rgbString[index] == ',')
		index++;
	*b = string_to_int(rgbString, &index);
	if (*b < 0)
		return (print_error("RGB values must be between 0 and 255.\n"), 1);
	return (0);
}

int	fill_colors(t_cub *cub)
{
	if (check_str_colors(cub, 0, -1, 0))
		return (1);
	if (parse_rgb(cub->ceiling, &cub->r_ceiling, \
	&cub->g_ceiling, &cub->b_ceiling) || \
	parse_rgb(cub->floor, &cub->r_floor, &cub->g_floor, &cub->b_floor))
		return (1);
	if (cub->r_ceiling < 0 || cub->r_ceiling > 255 || cub->g_ceiling < 0 || \
	cub->g_ceiling > 255 || cub->b_ceiling < 0 || cub->b_ceiling > 255 || \
	cub->r_floor < 0 || cub->r_floor > 255 || cub->g_floor < 0 || \
	cub->g_floor > 255 || cub->b_floor < 0 || cub->b_floor > 255)
		return (print_error("RGB values must be between 0 and 255.\n"), 1);
	return (0);
}
