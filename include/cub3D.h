/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:23 by lemercie          #+#    #+#             */
/*   Updated: 2025/03/19 10:12:55 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <errno.h>

enum e_errors
{
	DOUBLE_COLOR_ID = -100,
	DOUBLE_WALL_ID,
	WRONG_RGB_VALUE,
	EXTRA_VALUE,
	NOT_IDENTIFIER,
	MAP_NOT_LAST,
	INFO_MISSING,
	IDENTIFIER_WITHOUT_VALUE,
	MULT_PLAYER,
	WRONG_CHAR,
	WALL_ERROR,
	NO_PLAYER,
	NEWLINE_IN_MAP,
	PLAYER_OUTSIDE
};

enum e_location
{
	FLOOR,
	CEILING
};

typedef struct s_surrounding_chars
{
	char	left;
	char	right;
	char	up;
	char	down;
}	t_chars;

// how many radians to turn on one keypress
const static double	g_cam_turn_speed = 0.04;
// how many tiles to walk on one keypress
const static double	g_player_walk_speed = 0.1;
// field-of-view
const static double	g_fov = 0.66;

typedef struct s_map_line
{
	char		*line;
	int			length;
	struct s_map_line	*next;
	struct s_map_line	*previous;
}	t_map_line;

typedef struct s_point_double
{
	double	x;
	double	y;
}	t_point_double;

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

typedef struct s_draw
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	int				image_width;
	int				image_heigth;
	t_point_double	player_pos;
	t_point_double	player_dir;
	t_point_double	camera_plane;
} t_draw;

typedef struct s_rbg 
{
	int r;
	int g;
	int b; 
}	t_rgb;

typedef struct s_input
{
	int				identifier_counter;
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	char    		**map;
}	t_input;

typedef struct s_cub3D
{
	t_input input;
	t_draw	draw;
}	t_cub3D;

//validate_args.c
void	validate_arguments(int argc, char **argv);


//colors.c
int32_t convert_color(int32_t r, int32_t g, int32_t b, int32_t a);
//game_loop.c
void	start_graphics(int image_width, int image_heigth, t_cub3D *main_struct);
void	game_hook(void *param);

//draw_tools.c
void	 draw_vert_line(mlx_image_t *image, int x, int start_y, int end_y, \
	uint32_t color);
void	draw_floor_and_ceiling(t_cub3D *main_struct);
	
//cam_move.c
void	cam_move_fwd(t_cub3D *main_struct);
void	cam_move_back(t_cub3D *main_struct);
void	cam_strafe_left(t_cub3D *main_struct);
void	cam_strafe_right(t_cub3D *main_struct);
//cam_turn.c
void	cam_turn_left(t_cub3D *main_struct);
void	cam_turn_right(t_cub3D *main_struct);
//memory.c
void	free_everything(t_cub3D	*main_struct, t_map_line **map);
void	free_map_list(t_map_line **map);
void	free_map_nodes(t_map_line **map);
void	empty_gnl_buffer(int fd);
	
//parse_file.c
void    parse_input(int fd, t_cub3D *main_struct);

//parse_line.c
void	parse_line(char **line, int fd, t_map_line **map, t_cub3D *main_struct);

//set_player.c
void	set_player(t_map_line *current, t_cub3D *main_struct, int i,
	char direction);

//error.c
int	print_error_message(int return_value);

//color_parsing.c
int	set_floor_ceiling(char *type_identifier, char *color_code,
	t_cub3D *main_struct);

//texture_parsing.c
int	set_wall_texture(char *type_identifier, char *texture,
	t_cub3D *main_struct);

//map_parsing.c
int	start_of_map(char **line, int fd, t_cub3D *main_struct);
int	parse_map(char **line, int fd, t_map_line **map, t_cub3D *main_struct);

//map_validation.c
int	validate_map(t_map_line **map);
int	check_forbidden_chars(t_map_line *current, t_cub3D *main_struct);

//raycaster.c
void	draw(t_draw *data, t_cub3D *main_struct);

//map_validation_utils.c
int	check_zero(t_map_line *current, int i);
int	check_player(t_map_line *current, int i);
int	rest_is_whitespace(int fd);

#endif
