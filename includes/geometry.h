/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:03:02 by ndemont           #+#    #+#             */
/*   Updated: 2021/02/15 19:26:02 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H
# include <unistd.h>
# include <stdio.h>
# include <math.h>

typedef struct		s_pos
{
	int				i;
	int				j;
}					t_pos;

typedef struct		s_resolution
{
	int				width;
	int				height;
}					t_resolution;

typedef struct		s_vector
{
	float			coord[3];
}					t_vector;

typedef struct		s_matrix
{
	t_vector		r1;
	t_vector		r2;
	t_vector		r3;
	t_vector		r4;
}					t_matrix;

typedef struct		s_light
{
	t_vector		o;
	t_vector		c;
	float			i;
}					t_light;

typedef struct		s_ambiant
{
	float			i;
	t_vector		color;
}					t_ambiant;

typedef struct		s_ray
{
	t_vector		o;
	t_vector		d;
}					t_ray;

typedef struct		s_camera
{
	float			f;
	t_vector		o;
	t_vector		c;
}					t_camera;

typedef struct		s_pixel
{
	int				p;
	char			r;
	char			g;
	char			b;
}					t_pixel;

typedef struct		s_object
{
	int				type;
	t_vector		c;
	t_vector		o;
	t_vector		d;
	t_vector		t1;
	t_vector		t2;
	t_vector		t3;
	t_vector		p;
	float			h;
	float			diam;

}					t_object;

typedef struct		s_img
{
	void			*img_ptr;
	unsigned char	*data_addr;
}					t_img;

typedef struct		s_pattern
{
	float			width;
	float			height;
	t_vector		a;
	t_vector		b;
}					t_pattern;

typedef struct		s_2d
{
	float u;
	float v;
}					t_2d;

typedef struct		s_scene
{
	float			r[2];
	t_ambiant		a;
	t_light			*lights;
	t_camera		*cameras;
	t_object		*objects;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	unsigned char	*data_addr;
	int				bits_per_pixel;
	int				size;
	int				endian;
	int				ret;
	int				cam_i;
	int				cam_nbr;
	t_resolution	reso;
	t_img			*images;
	int				filter;
}					t_scene;

t_vector			color_limit(t_vector v);
float				intensity_limit(float i);
t_vector			find_intensity(t_vector h, float *i, t_vector n, t_scene s);
float				check_shadow(t_scene *s, t_vector inter, t_vector n, int l);

float				scalaire(t_vector v1, t_vector v2);
float				get_norme(t_vector v);
float				get_norme_2(t_vector v1);
void				normalize(t_vector *v);
t_vector			get_normalized(t_vector v);

int					near_inter(t_ray r, t_scene *s, t_vector *i, t_vector *n);
int					inter(t_ray r, t_object sp, t_vector *hit, t_vector *n);
float				inter_tr(t_ray r, t_object sp, t_vector *hit, t_vector *n);
float				inter_cy(t_ray r, t_object cy, t_vector *hit, t_vector *n);
float				inter_sp(t_ray r, t_object sp, t_vector *hit, t_vector *n);
float				inter_sq(t_ray r, t_object sq, t_vector *hit, t_vector *n);
float				inter_pl(t_ray r, t_object sp, t_vector *hit, t_vector *n);
float				inter_cl(t_ray r, t_object cl, t_vector *hit, t_vector *n);
float				inter_type(t_ray r, t_object o, t_vector *hit, t_vector *n);

t_vector			init_vector(float x, float y, float z);
t_vector			v_plus_i(t_vector v, float i);
t_vector			v_minus_i(t_vector v, float i);
t_vector			v_mult_i(t_vector v, float i);
t_vector			v_div_i(t_vector v, float i);
t_vector			v_plus_v(t_vector v1, t_vector v2);
t_vector			v_minus_v(t_vector v1, t_vector v2);
t_vector			v_mult_v(t_vector v1, t_vector v2);
t_vector			v_dot_v(t_vector v1, t_vector v2);
t_vector			v_mult_m(t_vector v, t_matrix m);

void				set_plan(t_scene *s);

float				quadratic_resolution(float a, float b, float c, float t[2]);

char				*parsing_a(char **line, t_scene *elem);
char				*parsing_r(char **line, t_scene *elem);
char				*parsing_c(char **line, t_scene *elem);
char				*parsing_l(char **line, t_scene *elem);
char				*parsing_sp(char **line, t_scene *elem);
char				*parsing_sq(char **line, t_scene *elem);
char				*parsing_cy(char **line, t_scene *elem);
char				*parsing_tr(char **line, t_scene *elem);
char				*parsing_pl(char **line, t_scene *elem);
char				*parsing_cl(char **line, t_scene *elem);
char				*parsing_st(char **line, t_scene *elem);

#endif
