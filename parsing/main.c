/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:41:28 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/03 13:59:54 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_cube(t_cub *cub)
{
	int	i;

	i = 0;
	printf("NO: %s\n", cub->no);
	printf("SO: %s\n", cub->so);
	printf("WE: %s\n", cub->we);
	printf("EA: %s\n", cub->ea);
	printf("F: %s\n", cub->floor);
	printf("C: %s\n\n", cub->ceiling);
	printf("RVB FLOOR: %d %d %d\n", cub->r_floor, cub->g_floor, cub->b_floor);
	printf("RVB CEILING: %d %d %d\n\n", cub->r_ceiling, cub->g_ceiling, cub->b_ceiling);
	while (cub->map[i])
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
	printf("\nMap width: %d\n", cub->map_width);
	printf("Map height: %d\n\n", cub->map_height);
	printf("Player direction: %c\n", cub->player.direction);
	printf("Player position: x = %i ; y = %i\n", cub->player.x, cub->player.y);
}

void	free_cube(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub)
		return;
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	free(cub->floor);
	free(cub->ceiling);
	while (cub->map[i])
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
}

int	basic_errors(char *filename)
{
	int		fd;
	char	buffer[BUFFER_SIZE];

	if (is_cub_file(filename) == 0) 
		return (print_error("Le fichier n'est pas un fichier .cub\n"), 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Erreur lors de l'ouverture du fichier\n"), 1);
	if (check_first_param(0, 0, fd, buffer) == 1)
		return (1);
	return (0);
}

int	test_path(t_cub *cub)
{
	if (open(cub->no, O_RDONLY) == -1)
		return (print_error("Erreur lors de l'ouverture de NO\n"), 1);
	if (open(cub->so, O_RDONLY) == -1)
		return (print_error("Erreur lors de l'ouverture de SO\n"), 1);
	if (open(cub->we, O_RDONLY) == -1)
		return (print_error("Erreur lors de l'ouverture de WE\n"), 1);
	if (open(cub->ea, O_RDONLY) == -1)
		return (print_error("Erreur lors de l'ouverture de EA\n"), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*filename;
	t_cub	cub;

	if (argc != 2)
		return (print_error("Nombre d'arguments incorrect\n"), 1);
	filename = argv[1];
	cub.ea_state = 0;
	cub.no_state = 0;
	cub.so_state = 0;
	cub.we_state = 0;
	cub.floor_state = 0;
	cub.ceiling_state = 0;
	if (basic_errors(filename) == 1)
		return (1);
	if (fill_cub_structure(&cub, filename) != 0)
		return (print_error("Erreur lors du remplissage de la structure\n"), 1);
	if (is_map_close(&cub) == -1)
		return (free_cube(&cub), 0);
	if (test_path(&cub) == 1)
		return (free_cube(&cub), 1);
	print_cube(&cub);
	if (exec_main(&cub) == -1)
		free_cube(&cub);
	return (0);
}
