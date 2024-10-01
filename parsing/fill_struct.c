/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:08:42 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/30 13:09:37 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_existence(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!cub->ea_state)
			return (cub->ea = ft_strdup(line + 3), cub->ea_state = 1, 0);
		else
			return (1);
	}
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!cub->floor_state)
			return (cub->floor = ft_strdup(line + 2), cub->floor_state = 1, 0);
		else
			return (1);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!cub->ceiling_state)
			return (cub->ceiling = ft_strdup(line + 2), \
			cub->ceiling_state = 1, 0);
		else
			return (1);
	}
	return (0);
}

int	parse_configuration_line(char *line, t_cub *cub)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!cub->no_state)
			return (cub->no = ft_strdup(line + 3), cub->no_state = 1, 0);
		else
			return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!cub->so_state)
			return (cub->so = ft_strdup(line + 3), cub->so_state = 1, 0);
		else
			return (1);
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!cub->we_state)
			return (cub->we = ft_strdup(line + 3), cub->we_state = 1, 0);
		else
			return (1);
	}
	if (check_existence(line, cub))
		return (1);
	return (0);
}

int	read_configuration(int fd, t_cub *cub)
{
	char	*line;

	while ((cub->lines_read < 6))
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
		(cub->lines_read)++;
	}
	if (cub->lines_read == 6 && !check_param_completed(cub))
		return (print_error("Error: missing args\n"), close(fd), 1);
	return (0);
}

int	read_map(int fd, t_cub *cub, char	*line, char	*map_temp)
{
	map_temp = ft_strjoin(map_temp, line);
	if (map_temp == NULL)
		return (malloc_error(line, 1, fd), 1);
	free(line);
	(cub->lines_read)++;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_valid_map(line))
			return (free(map_temp), malloc_error(line, 2, fd), 1);
		map_temp = ft_strjoin(map_temp, line);
		if (map_temp == NULL)
			return (malloc_error(line, 1, fd), 1);
		(cub->lines_read)++;
		free(line);
	}
	cub->map = ft_split(map_temp, '\n');
	if (cub->map == NULL)
		return (free(map_temp), close(fd), 1);
	return (count_dimensions(cub), 0);
}

int	fill_cub_structure(t_cub *cub, const char *filename, char *line)
{
	int	fd;

	cub->lines_read = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Error when opening file\n"), 1);
	if (read_configuration(fd, cub) != 0)
		return (1);
	if (cub->lines_read != 6)
		return (print_error("Error: missing args\n"), close(fd), 1);
	line = get_next_line(fd);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (read_map(fd, cub, line, ft_strdup("")) != 0)
		return (1);
	if (fill_colors(cub))
		return (1);
	if (get_player_position(cub, 0, 0) == -1)
		return (1);
	close(fd);
	return (0);
}
