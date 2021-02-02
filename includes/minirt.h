#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include "geometry.h"
# include "libft.h"
# include "printf.h"
# include "get_next_line.h"

int			check_file(char *filename);
char	    *check_parsing(char *file, t_scene *s);
int         ft_event(int keycode, t_scene *s);
int         ft_close_win(int keycode, t_scene *s);
void        color_img(t_scene *s);
void	    print_window(void *mlx_ptr, void *win_ptr, void *img_ptr);
int         ft_switch_cam(int keycode, t_scene *s);

#endif