/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:58:54 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/25 13:15:30 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*fill_path(char *line, char *path, int i, int j)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0' || line[i] == '\n')
				break ;
			else
				return (print_error("Error: invalid path\n"), NULL);
		}
		path[j] = line[i];
		i++;
		j++;
	}
	path[j] = '\0';
	return (path);
}

char	*get_path(char *line)
{
	int		i;
	int		j;
	char	*path;

	path = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!path)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	path = fill_path(line, path, i, j);
	if (!path)
		return (NULL);
	free(line);
	return (path);
}

int	test_path(t_cub *cub)
{
	cub->no = get_path(cub->no);
	cub->so = get_path(cub->so);
	cub->we = get_path(cub->we);
	cub->ea = get_path(cub->ea);
	if (compare_textures(cub))
		return (1);
	cub->fd_no = open(cub->no, O_RDONLY);
	if (cub->fd_no == -1)
		return (print_error("Error when opening NO\n"), 1);
	cub->fd_so = open(cub->so, O_RDONLY);
	if (cub->fd_so == -1)
		return (close(cub->fd_no), print_error("Error when opening SO\n"), 1);
	cub->fd_we = open(cub->we, O_RDONLY);
	if (cub->fd_we == -1)
		return (close(cub->fd_no), close(cub->fd_so), \
		print_error("Error when opening WE\n"), 1);
	cub->fd_ea = open(cub->ea, O_RDONLY);
	if (cub->fd_ea == -1)
		return (close(cub->fd_no), close(cub->fd_so), \
		close(cub->fd_we), print_error("Error when opening EA\n"), 1);
	return (close(cub->fd_no), close(cub->fd_so), close(cub->fd_we), \
	close(cub->fd_ea), 0);
}
