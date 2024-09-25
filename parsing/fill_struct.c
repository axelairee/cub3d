/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:08:42 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/25 12:24:15 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_configuration_line(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !cub->no_state)
		return (cub->no = ft_strdup(line + 3), cub->no_state = 1, 0);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !cub->so_state)
		return (cub->so = ft_strdup(line + 3), cub->so_state = 1, 0);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !cub->we_state)
		return (cub->we = ft_strdup(line + 3), cub->we_state = 1, 0);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !cub->ea_state)
		return (cub->ea = ft_strdup(line + 3), cub->ea_state = 1, 0);
	else if (ft_strncmp(line, "F ", 2) == 0 && !cub->floor_state)
		return (cub->floor = ft_strdup(line + 2), cub->floor_state = 1, 0);
	else if (ft_strncmp(line, "C ", 2) == 0 && !cub->ceiling_state)
		return (cub->ceiling = ft_strdup(line + 2), cub->ceiling_state = 1, 0);
	return (0);
}

int	struct_completed(t_cub *cub)
{
	if (cub->no_state && cub->so_state && cub->we_state && cub->ea_state \
	&& cub->floor_state && cub->ceiling_state)
		return (1);
	return (0);
}

int	read_configuration(int fd, t_cub *cub, int *lines_read)
{
	char	*line;

	while ((*lines_read < 6))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (!is_valid_line(line))
			return (read_till_end_of_file(fd), free(line), \
			print_error("Error: invalid line or missing args\n"), \
			close(fd), 1);
		if (parse_configuration_line(line, cub))
			return (free(line), read_till_end_of_file(fd), \
			print_error("Error: double args\n"), close(fd), 1);
		free(line);
		(*lines_read)++;
	}
	if (*lines_read == 6 && !check_param_completed(cub))
		return (print_error("Error: missing args\n"), close(fd), 1);
	return (0);
}

int	read_map(int fd, t_cub *cub, int *lines_read, char	*map_temp)
{
	char	*line;

	line = get_next_line(fd);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	map_temp = ft_strjoin(map_temp, line);
	free(line);
	(*lines_read)++;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_valid_map(line))
			return (free(line), free(map_temp), read_till_end_of_file(fd), \
			print_error("Error: invalid line on map\n"), close(fd), 1);
		map_temp = ft_strjoin(map_temp, line);
		(*lines_read)++;
		free(line);
	}
	cub->map = ft_split(map_temp, '\n');
	return (count_dimensions(cub), 0);
}

int	fill_cub_structure(t_cub *cub, const char *filename)
{
	int	fd;
	int	lines_read;

	lines_read = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Error when opening file\n"), 1);
	if (read_configuration(fd, cub, &lines_read) != 0)
		return (1);
	if (read_map(fd, cub, &lines_read, ft_strdup("")) != 0)
		return (1);
	if (fill_colors(cub))
		return (1);
	if (get_player_position(cub, 0, 0) == -1)
		return (1);
	close(fd);
	return (0);
}
