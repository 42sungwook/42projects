/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungwook <sungwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:01:26 by sungwook          #+#    #+#             */
/*   Updated: 2023/01/03 16:01:27 by sungwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h"

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_EXIT			17
# define KEY_ESC					53
# define KEY_W						13
# define KEY_A						0
# define KEY_S						1
# define KEY_D						2
# define KEY_R						15
# define KEY_K						40
# define MAP_USER					-4
# define MAP_EXIT					-3
# define MAP_COLLECTABLE			-2
# define MAP_WALL					-1
# define MAP_BLACK					0

typedef struct s_map_list
{
	char				*line;
	struct s_map_list	*next;
}						t_map_list;

typedef struct s_user
{
	void	*user_e0;
	void	*user_e1;
	void	*user_e2;
	void	*user_s0;
	void	*user_s1;
	void	*user_s2;
	void	*user_w0;
	void	*user_w1;
	void	*user_w2;
	void	*user_n0;
	void	*user_n1;
	void	*user_n2;
	int		d;
	int		pre_x;
	int		pre_y;
	int		x;
	int		y;
	int		move;
	int		endian;
}				t_user;

typedef struct s_custom
{
	void	*ball;
	void	*ball2;
	void	*ball3;
	void	*ball4;
	void	*stone;
	void	*ladder;
	void	*tile0;
	void	*tile1;
	void	*n_box;
	char	*addr;
	void	*enemy;
	int		left_ball;
	int		cnt;
	int		x;
	int		y;
}				t_custom;

typedef struct s_map
{
	int		c;
	int		p;
	int		e;
	int		x_size;
	int		y_size;
	int		total_move;
}				t_map;

typedef struct s_node
{
	int				x;
	int				y;
	int				idx;
	int				enemy_dir;
	int				enemy_alive;
	int				pre_val;
	int				**map;
	struct s_node	*next;
	struct s_deque	*way;
}				t_node;

typedef struct s_deque
{
	int		cnt;
	t_node	*front;
}				t_deque;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			**map1;
	int			**map2;
	char		**map;
	int			start;
	char		*addr;
	int			key_sign;
	int			reset;
	int			random;
	void		*game_start;
	void		*end_img;
	void		*game_over;
	size_t		level;
	t_user		user;
	t_custom	custom;
	t_map		map_v;
	t_deque		*site_deque;
	t_deque		*enemy_list;
}				t_game;

//draw
void	draw_start(t_game *g);
void	draw_map(t_game *g);
void	*dir_img(t_game *g, int d);
void	draw_move_e(t_game *g);
void	draw_move_w(t_game *g);
void	draw_move_n(t_game *g);
void	draw_move_s(t_game *g);
void	draw_user(t_game *g);
void	put_image_to_window(t_game *g, int x, int y, void *image);
void	*file_to_image(void *mlx, char *addr);
void	draw_enemy(t_game *g);
void	draw_catch_enemy(t_game *g, t_node *temp, size_t time);
void	draw_left_ball_count(t_game *g);
void	draw_step_count(t_game *g);
void	make_enemy_dir(t_node *temp);
void	enemy_deque_back(t_game *g, t_node *temp, int x, int y);
void	dir_enemy3(t_game *g, t_node *temp, int x, int y);
void	dir_enemy2(t_game *g, t_node *temp, int x, int y);
void	dir_enemy1(t_game *g, t_node *temp, int x, int y);
void	dir_enemy0(t_game *g, t_node *temp, int x, int y);
void	dir_enemy(t_game *g, t_node *temp, int x, int y);

//initalize
void	init_custom(t_custom *new);
void	init_map_v(t_map *new);
void	game_init(t_game *new, char *argv);
void	init_user_img(t_game *g, void *mlx);
void	init_custom_img(t_game *g, void *mlx);
void	init_start(t_game *game, int *x_width, int *y_width);
void	init_enemy(t_game *g);
void	make_enemy_list(t_game *g);

//make map
void	read_map(t_game *game);
t_node	*new_node(int x, int y);
t_deque	*new_deque(void);
void	deque_add_back(t_deque *deque, t_node *node);
int		delete_deque(t_deque *deque);
void	delete_front_deque(t_deque *deque);
void	delete_back_deque(t_deque *deque);
void	deque_back(t_deque *deque, int x, int y);
t_node	*new_node_2(int x, int y, int idx);
int		map_check_way(t_game *g);
int		map_check(t_game *g);
void	check_valid(t_game	*g);
void	delete_complete_deque(t_deque *deque, t_game *g);

// case check
void	find_site(int **arr, t_game *game);
void	case_check(t_game *g);
void	game_next_start(t_game *g);
int		game_restart(t_game *g);
void	case_eat_collectable(t_game *g, int x, int y);
void	case_enter_escape(t_game *g);
void	put_game_over_img(t_game *g);
void	put_game_end_img(t_game *g);
int		player_meet_enemy(t_game *g);
void	catch_enemy(t_game *g);

//utils
int		**make_int_map(t_game *g, size_t i, size_t j);
void	ft_free(int **arr, t_game *g);
int		check_str(char *str1, char *str2);
char	*ft_itoa(int n);
int		**dup_arr(int **arr, int size_x, int size_y);
void	make_enemy_map(int **map, t_game *g);
int		close_game(t_game *g);
void	ft_free2(char **arr);

//main
void	game_start(t_game *game);

#endif