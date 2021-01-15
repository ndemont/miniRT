#ifndef GEOMETRY_H
# define GEOMETRY_H

typedef struct	s_vector
{
	float		coord[3];
}				t_vector;

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
	t_vector	p;
	float		h;
	float		diam;

}				t_object;

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
	int				*data_addr2;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				ret;
}				t_scene;



int		ft_power(int nb, int power);

float		scalaire(t_vector v1, t_vector v2);
float		get_norme_2(t_vector v1);
void		normalize(t_vector *v);
int			inter(t_ray ray, t_object sphere, t_vector *inter, t_vector *normal);
int			inter2(t_ray ray, t_object *sp, t_vector *inter, t_vector *normal);
double		inter3(t_ray ray, t_object *sp, t_vector *inter, t_vector *normal);
float		inter_tr(t_ray ray, t_object sp, t_vector *inter, t_vector *N);
float		inter_sp(t_ray ray, t_object sp, t_vector *inter, t_vector *normal);
float		inter_pl(t_ray ray, t_object sp, t_vector *inter, t_vector *N);
float		inter_type(t_ray ray, t_object o, t_vector *inter, t_vector *N);
int			closest_inter(t_ray ray, t_scene s, t_vector *inter, t_vector *N);

t_vector	get_normalized(t_vector v);
float		distance(t_vector v1, t_vector v2);

t_vector	v_plus_i(t_vector v, float i);
t_vector	v_mult_i(t_vector v, float i);
t_vector	v_mult_v(t_vector v1, t_vector v2);
t_vector	v_div_i(t_vector v, float i);
t_vector	v_plus_v(t_vector v1, t_vector v2);
t_vector	v_minus_v(t_vector v1, t_vector v2);

void		parsing_a2(char **line, t_scene *elem);
void		parsing_r2(char **line, t_scene *elem);
void		parsing_c2(char **line, t_scene *elem);
void		parsing_l2(char **line, t_scene *elem);
void		parsing_sp2(char **line, t_scene *elem);
void		parsing_sq2(char **line, t_scene *elem);
void		parsing_cy2(char **line, t_scene *elem);
void		parsing_tr2(char **line, t_scene *elem);
void		parsing_pl2(char **line, t_scene *elem);

float		ft_atof(const char *str);

#endif
