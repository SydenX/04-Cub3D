/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:56:19 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/25 11:48:41 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "keymap.h"
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

# define HITBOX 35
# define MINIMAP_HITBOX 15
# define PLAYER_SIZE 3
# define WIDTH 1920
# define HEIGHT 1080

#define FOV (M_PI / 3) // Field of view

# define ERROR_INPUTFILE "Unable to read the input file."
# define ERROR_NOTFORMATTED "File is not correctly formatted."
# define ERROR_NOTINTERESTS "Map doesn't contains the interest points needed."
# define ERROR_NOTSURROUNDED "Map must be surrounded by walls."
# define ERROR_DOORNOTPARSED "Doors must be between only 2 walls on the same axis."
# define ERROR_ALLOCATION "Error during allocation."
#define ERROR_ ""

typedef enum e_direction {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	LAT,
	LONG
}	t_direction;

typedef enum e_doorstate {
	OPEN,
	CLOSE,
	OPENNING,
	CLOSING
}	t_doorstate;

typedef enum e_type {
	FLOOR,
	WALL,
	SPAWN,
	DOOR,
	NULLT,
	ENDL,
}	t_type;

typedef struct s_prog {
	void	*mlx;
	void	*win;
}	t_prog;

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_img {
	t_type			type;
	t_direction		direction;
	void 			*img_ptr;
	char 			*img_pixels;
	int 			bpp;
	int 			size_line;
	int 			endian;
}	t_img;

typedef struct s_node {
	int				x;
	int				y;

	t_img			img_top;
	t_img			img_floor;
	t_img			img_N;
	t_img			img_E;
	t_img			img_S;
	t_img			img_W;
	
	t_type			type;

	t_doorstate		door_state;
	int				running_door;
	int				door_loc;
	int				door_loc_map;
	
	int				is_free;
	
	t_direction		direction;
}	t_node;

typedef struct s_distance {
	float	d;
	t_type	type;
} t_distance;

typedef struct s_player {
	double 			x;
	double			y;
	double 			yaw;

	double			newx;
	double			newy;

	double			oldx;
	double			oldy;
	double			oldyaw;

	double			speed;
	double			sensivity;

	double			forwarding;
	double			lefting;
	double			backwarding;
	double			righting;

	double			righting_yaw;
	double			lefting_yaw;
	double			righting_yaw_key;
	double			lefting_yaw_key;
}	t_player;

typedef struct s_data {
	t_prog		*prog;
	t_node		*nodes;
	t_distance	*distance;
	t_player	player;
	t_img		img;
	
	void		*txt_path_north;
	void		*txt_path_east;
	void		*txt_path_south;
	void		*txt_path_west;
	t_rgb		f;
	t_rgb		c;
	
	int			*mousex;
	int			*mousey;
	
	int			in_menu;
	int			moves;

	int			minimap_x;
	int			minimap_y;
	int			minimap_endx;
	int			minimap_endy;

	int fps;
	int frame;
}	t_data;

//MAIN
int		map_init(t_data *data);
int		close_window(t_data *data);
int		open_menu(t_data *data);
//UTILS
void	move_player(t_data *data);
//LINESIZE
int		linesize_checks(char *reader);
//GET_SIZES
int		node_size(char *path);
int		file_chars(char *path);
int		get_fd(char *path, void *toFree, void *toFree2);
//IMAGES_1
t_img	*get_player_image(t_data *data);
t_img	*get_img_at(t_img *list, int x, int y, int isfloor);
t_img	create_image(int x, int y, t_type type, t_prog *prog);
t_img	*load_images(t_img *imgs, t_node *list, t_prog *prog);
void	*get_image(t_prog *prog, t_type type);
//ERROR_1
void	clear(t_data *data, void *toFree, void *toFree2);
void	exit_error(char *error, t_data *data, void *toFree, void *toFree2);
void	error_filedonotexist(void *path, void *toFree2, t_data *data);
void	error_fileerror(void *path, void *toFree2, t_data *data);
void	error_texturefileincorect(void *path, void *toFree2, t_data *data);
//NODE_1
void	check_to_door(t_data *data, int x, int y);
t_node	create_node(char name, int x, int y);
t_node	find_exit_point(t_node *list);
int		update_node(t_node node, t_node *list);
int		is_node_free(float x, float y, t_data *data);
int		toggle_door(t_node *cpy, t_data *data);
//MAP_INIT
int		do_map_checks(int fd, char *reader);
t_node	*read_map(int fd, int fc, char *reader, t_data *data);
void	write_cubes(int color, int startX, int startY, t_data *data, int tailleX, int tailleY);
int	map_loop(t_data *data);
//MAP_SIZE
int	count_map(int fd, int x, char *reader);

// P2 ----------------=----------------=----------------=----------------=----------------=----------------

//PLAYER_MANAGER
t_player	init_player(t_node spawn);

//HOOKS_MANAGER
int		key_released(int key, t_data *data);
void	key_pressed(int key, t_data *data);
int		event_key_pressed(int keycode, t_data *datav);

int 	mouse_hook(int keycode, int x,int y,t_data *data);
void	get_mouse_move(t_data *data);

void	init_hooks(t_data *data);

//NODES_MANAGER
int		get_list_ylen(t_node *list);
int		get_list_xlen(t_node *list);
int		get_list_size(t_node *list);

t_node	*get_node_at(t_node *list, int x, int y);
t_node	find_spawn_point(t_node *list);
int		update_node(t_node node, t_node *list);
int		is_node_free(float x, float y, t_data *data);

void	check_to_door(t_data *data, int x, int y);
int		toggle_door(t_node *cpy, t_data *data);

//MAP_MANAGER
t_node	*check_nodes_type(t_node *nodes, int size);




//UTILS
int		ulimitor(int	tolimit, int limit);
int		limitor(int	tolimit, int limit);
int		get_map_width(t_data *data);
int		get_map_height(t_data *data);

//DEBUG
void	debugfps(t_data *data);
char	*get_frames(char *moves);
char	*get_fps(char *moves);
void	debug_affichage_frames(t_data *data);
unsigned long rgb_to_hex(t_rgb rgb);

#endif