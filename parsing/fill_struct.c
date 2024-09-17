/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:08:42 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/17 14:24:57 by abolea           ###   ########.fr       */
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
	{
		free_cube(cub);
		return (1);
	}
	return (0);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Erreur lors de l'ouverture du fichier\n");
	return (fd);
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

int	read_configuration(int fd, t_cub *cub, int *lines_read)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	char	*end_of_line;
	char	*line;
	char	*map_temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (*lines_read < 6 && (bytes_read > 0))
	{
		buffer[bytes_read] = '\0';
		line = buffer;
		while (*lines_read < 6 && (ft_strchr(line, '\n')) != NULL)
		{
			end_of_line = ft_strchr(line, '\n');
			*end_of_line = '\0';
			if (!is_valid_line(line))
				return (print_error("Erreur: ligne invalide\n"), close(fd), 1);
			if (parse_configuration_line(line, cub))
				return (print_error("Erreur: double args\n"), close(fd), 1);
			if (line[0] != '\0')
				(*lines_read)++;
			line = end_of_line + 1;
		}
	}
	map_temp = ft_strdup(line);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		map_temp = ft_strjoin(map_temp, buffer);
	}
	cub->map = ft_split(map_temp, '\n');
	count_dimensions(cub);
	if (*lines_read < 6 || bytes_read == -1)
		return (print_error("Erreur lors de la lecture des configurations\n"), \
		close(fd), 1);
	return (close(fd), 0);
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
		return (-1);
	return (0);
}

int	check_param_completed(t_cub *cub)
{
	if (!cub->no_state || !cub->so_state || !cub->we_state || !cub->ea_state \
	|| !cub->floor_state || !cub->ceiling_state)
		return (1);
	return (0);
}

int	fill_cub_structure(t_cub *cub, const char *filename)
{
	int	fd;
	int	lines_read;

	lines_read = 0;
	fd = open_file(filename);
	if (fd == -1)
		return (1);
	if (read_configuration(fd, cub, &lines_read) != 0 || check_param_completed(cub))
		return (1);
	if (get_player_position(cub, 0, 0) == -1)
		return (free_cube(cub), 1);
	if (compare_textures(cub))
		return (1);
	if (fill_colors(cub))
		return (1);
	return (0);
}
