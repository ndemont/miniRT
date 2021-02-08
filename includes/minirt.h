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

typedef struct  s_BmpHeader
{
    char            bitmapSbytes[2];
    int    sizeOfBmpFile;
    int    reservedBytes;
    int    pixelDataOffset;
}               t_BmpHeader;

typedef struct  s_BmpInfoHeader 
{
    int     sizeOfThisHeader;
    int     width;
    int     height;
    short int   numberOfColorPlanes;
    short int     colorDepth;
    int     compressionMethod;
    int     rawBitmapDataSize; 
    int     horizontalResolution; 
    int     verticalResolution;
    int     colorTableEntries;
    int     importantColors;
}               t_bmpInfoHeader;

typedef struct  s_pixel 
{
    char blue;
    char green;
    char red;
}               t_pixel;

int			check_file(char *filename);
char	    *check_parsing(char *file, t_scene *s);
int         ft_event(int keycode, t_scene *s);
int         ft_close_win(int keycode, t_scene *s);
void        color_img(t_scene *s);
void	    print_window(void *mlx_ptr, void *win_ptr, void *img_ptr);
int         ft_switch_cam(int keycode, t_scene *s);
char 		*leaks(char **split, char *error);
int         bmp_yay(t_scene *s);

char		*ft_check_coord(char *line, float c[3]);
char		*ft_check_color(char *line, float c[3]);

int			ft_strisfloat(char *str);
int			ft_strisdigit(char *str);
int			ft_cross(int keycode, t_scene *s);
t_img		ft_new_img(t_scene *s, int i);
int		ft_move_cam(int keycode, t_scene *s);


#endif