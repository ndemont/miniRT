#ifndef GEOMETRY_H
# define GEOMETRY_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct	s_vector
{
	float		coord[3];
}				t_vector;

typedef struct	s_matrix
{
	t_vector r1;
	t_vector r2;
	t_vector r3;
	t_vector r4;
}				t_matrix;

typedef struct	s_light
{
	t_vector	o;
	t_vector	c;
	float		i;
}				t_light;

typedef struct	s_ambiant
{
	float		i;
	t_vector	color;
}				t_ambiant;

typedef struct	s_ray
{
	t_vector	o;
	t_vector	d;
}				t_ray;

typedef struct	s_sphere
{
	t_vector	o;
	float		r;
	t_vector	albedo;
}				t_sphere;

typedef struct	s_camera
{
	float		f;
	t_vector	o;
	t_vector	c;
}				t_camera;

typedef struct	s_object
{
	int			type;
	t_vector	c;
	t_vector	o;
	t_vector	d;
	t_vector	t1;
	t_vector	t2;
	t_vector	t3;
	t_vector	p;
	float		h;
	float		diam;

}				t_object;

typedef struct	s_img
{
	void			*img_ptr;
	unsigned char	*data_addr;
}				t_img;


typedef struct	s_scene
{
	float			R[2];
	t_ambiant		A;
	t_light			*lights;
	t_camera		*cameras;
	t_object		*objects;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned char	*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				ret;
	int				cam_i;
	int				cam_nbr;
	t_img			*images;
}				t_scene;


t_vector	color_limit(t_vector v);

float		intensity_limit(float i);

int			ft_power(int nb, int power);

float		scalaire(t_vector v1, t_vector v2);
float		get_norme(t_vector v);
float		get_norme_2(t_vector v1);
void		normalize(t_vector *v);
int			inter(t_ray ray, t_object sphere, t_vector *inter, t_vector *normal);
float		inter_tr(t_ray ray, t_object sp, t_vector *inter, t_vector *N);
float		inter_cy(t_ray ray, t_object cy, t_vector *inter, t_vector *N);
float		inter_sp(t_ray ray, t_object sp, t_vector *inter, t_vector *normal);
float		inter_sq(t_ray ray, t_object sq, t_vector *inter, t_vector *N);
float		inter_pl(t_ray ray, t_object sp, t_vector *inter, t_vector *N);
float		inter_type(t_ray ray, t_object o, t_vector *inter, t_vector *N);
int			closest_inter(t_ray ray, t_scene *s, t_vector *inter, t_vector *N);

float		check_shadow(t_scene *s, t_vector inter, t_vector N, int l);

t_vector	init_vector(float x, float y, float z);

void		set_plan(t_scene *s);

float		quadratic_resolution(float a, float b, float c, float t[2]);
t_vector	find_intensity(t_vector inter, float *fint, t_vector N, t_scene s);


t_vector	get_normalized(t_vector v);

t_vector	v_plus_i(t_vector v, float i);
t_vector	v_minus_i(t_vector v, float i);
t_vector	v_mult_i(t_vector v, float i);
t_vector	v_mult_v(t_vector v1, t_vector v2);
t_vector	v_div_i(t_vector v, float i);
t_vector	v_plus_v(t_vector v1, t_vector v2);
t_vector	v_minus_v(t_vector v1, t_vector v2);
t_vector	v_produit_v(t_vector v1, t_vector v2);
t_vector	v_mult_m(t_vector v, t_matrix m);
float		scalaire(t_vector v1, t_vector v2);

char		*parsing_a(char **line, t_scene *elem);
char		*parsing_r(char **line, t_scene *elem);
char		*parsing_c(char **line, t_scene *elem);
char		*parsing_l(char **line, t_scene *elem);
char		*parsing_sp(char **line, t_scene *elem);
char		*parsing_sq(char **line, t_scene *elem);
char		*parsing_cy(char **line, t_scene *elem);
char		*parsing_tr(char **line, t_scene *elem);
char		*parsing_pl(char **line, t_scene *elem);

float		ft_atof(const char *str);

#endif
