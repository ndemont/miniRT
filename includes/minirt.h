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
# include <stdlib.h>
# include "get_next_line.h"

# ifdef LINUX
# define MOVE_R 65363
# define MOVE_L 65361
# define MOVE_F 65360
# define MOVE_B 65362
# define SWITCH_CAM
# define ESC 65307
# else
# define MOVE_R 0x7C
# define MOVE_L 0x7B
# define MOVE_F 0x7D
# define MOVE_B 0x7E
# define SWITCH_CAM 0x08
# define ESC 0x35
# endif

int			check_file(char *filename);
char	    *check_parsing(char *file, t_scene *s);
int         ft_event(int keycode, t_scene *s);
int         ft_close_win(int keycode, t_scene *s);
void        minirt(t_scene *s);
void	    print_window(void *mlx_ptr, void *win_ptr, void *img_ptr);
int         ft_switch_cam(int keycode, t_scene *s);
char 		*leaks(char **split, char *error);
int         bmp_yay(t_scene *s);

char		*ft_check_coord(char *line, float c[3]);
char		*ft_check_color(char *line, float c[3]);

int			ft_strisfloat(char *str);
int			ft_strisdigit(char *str);
int			ft_cross(int keycode, t_scene *s);
t_img		ft_new_img(t_scene *s);
void	ft_move_cam(int keycode, t_scene *s);
int 	init_scene(t_scene *s, char **list);
void	ft_count_elem(char **list, int *c, int *l, int *o);
char		*leaks(char **split, char *error);
int		print_errors(int error);
int		print_errors2(char *error);
t_matrix	rotation_matrix(t_scene s);
void	init_general(t_scene *s);


#endif
