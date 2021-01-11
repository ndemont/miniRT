#ifndef GEOMETRY_H
# define GEOMETRY_H

typedef struct	s_vector
{
	float		coord[3];
}				t_vector;

typedef struct	s_elem
{
	char		*type;
	float		size[2];
	t_vector	v;
	t_vector	v2;
	t_vector	origin;
	float		focal;
	t_vector	color;
	float		ratio;
	float		height;
	float		ray;

}				t_elem;

typedef struct	s_ray
{
	t_vector	o;
	t_vector	d;
}				t_ray;

typedef struct	s_light
{
	t_vector	o;
	float		i;
}				t_light;

typedef struct	s_sphere
{
	t_vector	o;
	float		r;
	t_vector	albedo;
}				t_sphere;

int		ft_power(int nb, int power);

float		scalaire(t_vector v1, t_vector v2);
float		get_norme_2(t_vector v1);
void		normalize(t_vector *v);
int			inter(t_ray ray, t_sphere sphere, t_vector *inter, t_vector *normal);
t_vector	get_normalized(t_vector v);

t_vector	v_plus_i(t_vector v, float i);
t_vector	v_mult_i(t_vector v, float i);
t_vector	v_mult_v(t_vector v1, t_vector v2);
t_vector	v_div_i(t_vector v, float i);
t_vector	v_plus_v(t_vector v1, t_vector v2);
t_vector	v_minus_v(t_vector v1, t_vector v2);

void		parsing_A(char **line, t_elem *elem);
void		parsing_R(char **line, t_elem *elem);
void		parsing_c(char **line, t_elem *elem);
void		parsing_l(char **line, t_elem *elem);
void		parsing_sp(char **line, t_elem *elem);
void		parsing_sq(char **line, t_elem *elem);
void		parsing_cy(char **line, t_elem *elem);
void		parsing_tr(char **line, t_elem *elem);
void		parsing_pl(char **line, t_elem *elem);

float		ft_atof(const char *str);

#endif
