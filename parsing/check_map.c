/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:41:34 by lle-pier          #+#    #+#             */
/*   Updated: 2024/08/28 16:43:12 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_cub_file(const char *filename)
{
	size_t	len;

	len = strlen(filename);
	if (len < 5)
		return (0);
	if (strcmp(filename + len - 4, ".cub") == 0)
		return (1);
	return (0);
}

int	is_valid_line(const char *line)
{
	if (line[0] == '\0' || strncmp(line, "NO", 2) == 0 \
	|| strncmp(line, "EA ", 3) == 0 || strncmp(line, "SO ", 3) == 0 \
	|| strncmp(line, "WE ", 3) == 0 || strncmp(line, "F ", 2) == 0 \
	|| strncmp(line, "C ", 2) == 0)
	{
		return (1);
	}
	return (0);
}

int	is_valid_map(const char *line)
{
	while (*line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != '2' && *line != 'N' \
		&& *line != 'S' && *line != 'E' && *line != 'W' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	check_first_param(int lines_read, ssize_t bytes_read, int fd, char *buffer)
{
	char	*end_of_line;
	char	*line;
	int		map;

	map = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0 && lines_read < 7)
	{
		buffer[bytes_read] = '\0';
		line = buffer;
		while (ft_strchr(line, '\n') != NULL && lines_read < 6)
		{
			end_of_line = ft_strchr(line, '\n');
			*end_of_line = '\0';
			if (!is_valid_line(line))
				return (print_error("Erreur: ligne invalide\n"), close(fd), 1);
			if (line[0] != '\0' || line[0] == '\n')
				lines_read++;
			line = end_of_line + 1;
			if (lines_read == 6)
				break ;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		while ((ft_strchr(line, '\n')) != NULL)
		{
			end_of_line = ft_strchr(line, '\n');
			*end_of_line = '\0';
			if (map == 0 && (line[0] == '\0' || line[0] == '\n'))
			{
				line = end_of_line + 1;
				continue ;
			}
			map = 1;
			lines_read++;
			if (line[0] == '\0' || line[0] == '\n')
				return (print_error("Erreur: ligne vide\n"), close(fd), 1);
			if (!is_valid_map(line))
				return (print_error("Erreur: carte invalide\n"), close(fd), 1);
			line = end_of_line + 1;
		}
	}
	if (lines_read < 6 || !is_valid_map(line))
		return (print_error("Erreur: coordonnees invalides\n"), close(fd), 1);
	if (bytes_read == -1)
		return (print_error("Erreur lors de la lecture du fichier\n"), \
		close(fd), 1);
	return (0);
}
