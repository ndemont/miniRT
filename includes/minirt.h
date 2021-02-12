/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:01:40 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/12 01:01:43 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include "geometry.h"
# include "libft.h"
# include "printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# define MAX_WIDTH_BMP 1920
# define MAX_HEIGHT_BMP 1080
# define MAX_WIDTH_MAC 1280
# define MAX_HEIGHT_MAC 720
# if LINUX == 1
#  define MOVE_R 65363
#  define MOVE_L 65361
#  define MOVE_F 65362
#  define MOVE_B 65364
#  define SWITCH_CAM 32
#  define ESC 65307
# else
#  define MOVE_R 0x7C
#  define MOVE_L 0x7B
#  define MOVE_F 0x7E
#  define MOVE_B 0x7D
#  define SWITCH_CAM 0x31
#  define ESC 0x35
# endif

int			check_file(char *filename);
char		*check_parsing(char *file, t_scene *s);
int			ft_event(int keycode, t_scene *s);
int			ft_close_win(int keycode, t_scene *s);
void		minirt(t_scene *s);
void		print_window(void *mlx_ptr, void *win_ptr, void *img_ptr);
int			ft_switch_cam(int keycode, t_scene *s);

char		*free_split(char **split, char *error);
char		*free_parsing(char *content);
int			free_scene(char **split, t_scene *s);

char		*save_bmp(t_scene *s);

char		*ft_check_coord(char *line, float c[3]);
char		*ft_check_color(char *line, float c[3]);

int			ft_strisfloat(char *str);
int			ft_strisdigit(char *str);
int			ft_cross(int keycode, t_scene *s);
t_img		ft_new_img(t_scene *s);
void		ft_move_cam(int keycode, t_scene *s);
int			init_scene(t_scene *s, char **list);
void		ft_count_elem(char **list, int *c, int *l, int *o);
int			print_errors(char *error);
t_matrix	rotation_matrix(t_scene s);
void		init_general(t_scene *s);

int			check_errors(int ac, char **av, t_scene *s);
void		init_images(t_scene *s);
t_pixel		find_color(t_scene *s, int obj, t_vector inter, t_vector normal);
void		bmp_image(t_scene *s);

#endif
