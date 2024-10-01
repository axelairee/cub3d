/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:41:28 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/30 13:09:52 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_cube(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub)
		return ;
	if (cub->no_state == 1)
		free(cub->no);
	if (cub->so_state == 1)
		free(cub->so);
	if (cub->we_state == 1)
		free(cub->we);
	if (cub->ea_state == 1)
		free(cub->ea);
	if (cub->floor_state == 1)
		free(cub->floor);
	if (cub->ceiling_state == 1)
		free(cub->ceiling);
	if (cub->map == NULL)
		return ;
	while (cub->map[i])
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
}

void	malloc_error(char *to_free, int i, int fd)
{
	free(to_free);
	close(fd);
	if (i == 1)
		print_error("Error: malloc error\n");
	else
		print_error("Error: invalid line on map\n");
	read_till_end_of_file(fd);
}

int	basic_errors(char *filename)
{
	if (is_cub_file(filename) == 0)
		return (print_error("File is not a .cub file\n"), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*filename;
	t_cub	cub;

	if (argc != 2)
		return (print_error("incorrect number of arguments\n"), 1);
	filename = argv[1];
	cub.ea_state = 0;
	cub.no_state = 0;
	cub.so_state = 0;
	cub.we_state = 0;
	cub.floor_state = 0;
	cub.ceiling_state = 0;
	cub.map = NULL;
	if (check_buffer() == 1 || basic_errors(filename) == 1)
		return (1);
	if (fill_cub_structure(&cub, filename, NULL) != 0)
		return (free_cube(&cub), \
		print_error("Error when filling structure\n"), 1);
	if (check_map_closed(&cub, 1, 1) == -1)
		return (free_cube(&cub), 0);
	if (test_path(&cub) == 1)
		return (free_cube(&cub), 1);
	if (exec_main(&cub) == -1)
		free_cube(&cub);
	return (free_cube(&cub), 0);
}
