/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:12:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/09/25 16:22:56 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <limits.h>

# define BUFFER_SIZE 10
# define SCREEN_W 1200
# define SCREEN_H 900

typedef struct s_pos
{
	int		x;
	int		y;
	int		angle;
	char	direction;
}				t_pos;

typedef struct s_cub
{
	char	*no;
	int		no_state;
	int		fd_no;
	char	*so;
	int		so_state;
	int		fd_so;
	char	*we;
	int		we_state;
	int		fd_we;
	char	*ea;
	int		ea_state;
	int		fd_ea;
	char	*floor;
	int		r_floor;
	int		g_floor;
	int		b_floor;
	int		floor_state;
	char	*ceiling;
	int		r_ceiling;
	int		g_ceiling;
	int		b_ceiling;
	int		ceiling_state;
	char	**map;
	int		map_width;
	int		map_height;
	t_pos	player;
}			t_cub;

typedef struct s_img
{
	void			*img;
	char			*data;
	int				bpp;
	int				tex_bpp;
	int				line_length;
	int				tex_line_length;
	int				endian;
	int				tex_endian;
	int				width;
	int				tex_width;
	int				height;
	int				tex_height;
	void			*img_ptr;
	void			*tex_ptr;
	void			*tex_data;
	int				pos;
	struct s_img	*north;
	struct s_img	*south;
	struct s_img	*east;
	struct s_img	*west;
}	t_img;

typedef struct reader
{
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE];
	char	*line;
	char	*end_of_line;
	char	*map_temp;
}	t_reader;

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_cardinal_direction;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	fg;
	int	fd;
}	t_keys;

typedef struct s_cam
{
	double	pos_x; //position x du joueur
	double	pos_y; //position y du joueur
	double	cam_x; //coordonne x du rayon dans l espace de la camera
	double	dir_x; // direction x du joueur
	double	dir_y; // direction y du joueur
	double	ray_dir_x; // direction x du rayon
	double	ray_dir_y; // direction y du rayon
	double	plane_x; // plan x de la camera
	double	plane_y; // plan y de la camera
	double	delta_dist_x; // distance rayon entre deux intersections
	double	delta_dist_y; // distance rayon entre deux intersections
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		dir;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		map_x;
	int		map_y;
	char	**map;
	int		is_open;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	int		c_color;
	int		f_color;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	t_keys	keys;
}	t_cam;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*xpm_ptr;
	t_cam	*cam;
	t_img	img;
	t_cub	*cub;
}	t_mlx;

char	*ft_strchr(const char *s, int c);
ssize_t	ft_strlen(const char *s);
void	print_error(const char *msg);
int		is_cub_file(const char *filename);
int		is_valid_line(const char *line);
int		is_valid_map(const char *line);
int		check_first_param(int linesRead, \
ssize_t bytesRead, int fd, char *buffer);
int		process_line(t_cub *cub, const char *line);
void	process_map_line(t_cub *cub, const char *line, int row);
int		fill_cub_structure(t_cub *cub, const char *filename);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_map_closed(t_cub *c, int i, int j);
char	*ft_strsub(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	print_cube(t_cub *cub);
void	free_cube(t_cub *cub);
int		fill_colors(t_cub *cub);
void	move_forward(t_cam *cam, char **map);
void	move_backward(t_cam *cam, char **map);
void	rotate_left(t_cam *cam);
void	rotate_right(t_cam *cam);
int		render_scene(t_mlx *mlx);
int		update_position(t_mlx *mlx);
int		handle_key_press(int keycode, void *param);
void	raycasting(t_cam *cam, int x);
void	dir_ray_map(t_cam *cam);
void	use_dda(t_cam *cam);
void	wall_height(t_cam *cam);
void	put_wall(t_cam *cam, t_img *img);
void	draw_px(t_img *img, t_cam *cam, t_mlx *mlx);
int		create_image(t_img *img, t_mlx *mlx);
void	put_pixel(t_img *img, int x, int y, int color);
void	color_floor_and_ceiling(t_img *img, t_cam *cam);
int		load_textures(t_img *img, t_mlx *mlx, char *filename);
int		handle_key_release(int keycode, void *param);
int		exec_main(t_cub *cub);
void	move_right(t_cam *cam, char **map);
void	move_left(t_cam *cam, char **map);
int		rgb_to_hex(int r, int g, int b);
void	draw_column(t_cam *cam, t_img *img, int x);
t_img	*get_dir(t_cam *cam, t_img *img);
t_cam	*init_argument(t_cub *cub);
int		init_textures(t_mlx *mlx, t_cub *cub);
int		handle_exit(t_mlx *mlx);
void	free_all(t_mlx *mlx, t_cam *cam, int i);
int		init_mlx(t_mlx *mlx, t_cub *cub);
int		compare_strings(const char *str1, const char *str2);
int		compare_textures(t_cub *cub);
int		open_file(const char *filename);
void	count_dimensions(t_cub *cub);
int		check_param_completed(t_cub *cub);
int		check_buffer(void);
char	*get_next_line(int fd);
char	*ft_free(char **str);
size_t	ft_strlen_gnl(const char *s);
char	*ft_charrchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		test_path(t_cub *cub);
int		get_player_position(t_cub *c, int x, int y);
void	read_till_end_of_file(int fd);
int		ft_strcmp(const char *s1, const char *s2);

#endif