#ifndef GEOMETRY_H
# define GEOMETRY_H

typedef struct	s_vector
{
	float		coord[3];
}				t_vector;

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
}				t_sphere;

int		ft_power(int nb, int power);

float		scalaire(t_vector v1, t_vector v2);
float		get_norme_2(t_vector v1);
void		normalize(t_vector *v);
int			inter(t_ray ray, t_sphere sphere, t_vector *inter, t_vector *normal);
t_vector	get_normalized(t_vector v);

t_vector	v_plus_i(t_vector v, float i);
t_vector	v_mult_i(t_vector v, float i);
t_vector	v_div_i(t_vector v, float i);
t_vector	v_plus_v(t_vector v1, t_vector v2);
t_vector	v_minus_v(t_vector v1, t_vector v2);

#endif
