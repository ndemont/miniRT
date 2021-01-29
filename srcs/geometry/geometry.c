#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <geometry.h>

float		quadratic_resolution(float a, float b, float c, float *t1, float *t2)
{
		float delta;

		delta = (b * b) - (4 * a * c);
		if (delta < 0)
			return (0);
		*t1 = (-b - (sqrt(delta))) / (2 * a);
		*t2 = (-b + (sqrt(delta))) / (2 * a);
		if (*t2 >= 0)
			return (1);
		else
			return (0);
}

float		scalaire(t_vector v1, t_vector v2)
{
	float rslt;

	rslt = (v1.coord[0] * v2.coord[0]) + (v1.coord[1] * v2.coord[1]) + (v1.coord[2] * v2.coord[2]);
	return (rslt);
}

float		intensity_limit(float i)
{
	if (i < 0)
		i = 0;
	if (i > 1)
		i = 1;
	return (i);
}

t_vector	color_limit(t_vector v)
{
	if (v.coord[0] > 255)
		v.coord[0] = 255;
	if (v.coord[1] > 255)
		v.coord[1] = 255;
	if (v.coord[2] > 255)
		v.coord[2] = 255;
	return (v);
}

float		distance(t_vector v1, t_vector v2)
{
	float rslt;

	rslt = powf((v2.coord[0] - v1.coord[0]), 2) + powf((v2.coord[1] - v1.coord[1]), 2) + powf((v2.coord[2] - v1.coord[2]), 2);
	if (!rslt)
		rslt = 0;
	else
		rslt = sqrt(rslt);
	return (rslt);
}

t_vector	v_plus_i(t_vector v, float i)
{
	t_vector v3;
	
	v3.coord[0] = v.coord[0] + i;
	v3.coord[1] = v.coord[1] + i;
	v3.coord[2] = v.coord[2] + i;
	return (v3);
}

t_vector	init_vector(float x, float y, float z)
{
	t_vector new;

	new.coord[0] = x;
	new.coord[1] = y;
	new.coord[2] = z;
	return (new);
}

t_vector	v_minus_i(t_vector v, float i)
{
	t_vector v3;
	
	v3.coord[0] = v.coord[0] - i;
	v3.coord[1] = v.coord[1] - i;
	v3.coord[2] = v.coord[2] - i;
	return (v3);
}

t_vector	v_mult_i(t_vector v, float i)
{
	t_vector v3;
	
	v3.coord[0] = v.coord[0] * i;
	v3.coord[1] = v.coord[1] * i;
	v3.coord[2] = v.coord[2] * i;
	return (v3);
}

t_vector	v_div_i(t_vector v, float i)
{
	t_vector v3;
	
	v3.coord[0] = v.coord[0] / i;
	v3.coord[1] = v.coord[1] / i;
	v3.coord[2] = v.coord[2] / i;
	return (v3);
}

t_vector	v_mult_m(t_vector v, t_matrix m)
{
	t_vector new;

	new.coord[0] = (m.r1.coord[0] * v.coord[0]) + (m.r2.coord[0] * v.coord[1]) + (m.r3.coord[0] * v.coord[2]);
	new.coord[1] = (m.r1.coord[1] * v.coord[0]) + (m.r2.coord[1] * v.coord[1]) + (m.r3.coord[1] * v.coord[2]);
	new.coord[2] = (m.r1.coord[2] * v.coord[0]) + (m.r2.coord[2] * v.coord[1]) + (m.r3.coord[2] * v.coord[2]);
	return (new);
} 

t_vector	v_plus_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] + v2.coord[0];
	v3.coord[1] = v1.coord[1] + v2.coord[1];
	v3.coord[2] = v1.coord[2] + v2.coord[2];
	return (v3);
}

t_vector	v_minus_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] - v2.coord[0];
	v3.coord[1] = v1.coord[1] - v2.coord[1];
	v3.coord[2] = v1.coord[2] - v2.coord[2];
	return (v3);
}

t_vector	v_mult_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] * v2.coord[0];
	v3.coord[1] = v1.coord[1] * v2.coord[1];
	v3.coord[2] = v1.coord[2] * v2.coord[2];
	return (v3);
}

t_vector	v_produit_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[1] * v2.coord[2] - v1.coord[2] * v2.coord[1];
	v3.coord[1] = v1.coord[2] * v2.coord[0] - v1.coord[0] * v2.coord[2];
	v3.coord[2] = v1.coord[0] * v2.coord[1] - v1.coord[1] * v2.coord[0];
	return (v3);
}

t_vector	v_div_v(t_vector v1, t_vector v2)
{
	t_vector v3;

	v3.coord[0] = v1.coord[0] / v2.coord[0];
	v3.coord[1] = v1.coord[1] / v2.coord[1];
	v3.coord[2] = v1.coord[2] / v2.coord[2];
	return (v3);
}

float		get_norme_2(t_vector v)
{
	float rslt;

	rslt = powf(v.coord[0], 2) + powf(v.coord[1], 2) + powf(v.coord[2], 2);
	return (rslt);
}

float		get_norme(t_vector v)
{
	float rslt;

	rslt = powf(v.coord[0], 2) + powf(v.coord[1], 2) + powf(v.coord[2], 2);
	if (!rslt)
		rslt = 0;
	return (rslt);
}

void		normalize(t_vector *v)
{
	float	norm;

	norm = sqrt(get_norme_2(*v));
	v->coord[0] = v->coord[0] / norm;
	v->coord[1] = v->coord[1] / norm;
	v->coord[2] = v->coord[2] / norm;
}

t_vector	get_normalized(t_vector v)
{
	normalize(&v);
	return (v);
}

float		inter_type(t_ray ray, t_object o, t_vector *inter, t_vector *N)
{
	float (*type[13])(t_ray, t_object, t_vector *, t_vector *);
	float t;

	type[4] = &inter_sp;
	type[6] = &inter_sq;
	type[8] = &inter_cy;
	type[10] = &inter_tr;
	type[12] = &inter_pl;
	t = (*type[o.type])(ray, o, inter, N);
	return (t);
}

void	set_plan(t_scene *s)
{
	t_ray		ray;
	float		scal;
	t_vector	normal;
	int 		i;

	i = 0;
	while (s->objects[i].type != -1)
	{
		ray.o = s->cameras[s->cam_i].o;
		ray.d = s->cameras[s->cam_i].c;
		normalize(&ray.d);
		if (s->objects[i].type == 6 || s->objects[i].type == 12)
		{
			normal = get_normalized(s->objects[i].d);
			scal = scalaire(v_minus_v(s->objects[i].o, ray.o), normal);
			if (scal > 0)
				s->objects[i].d = v_mult_i(s->objects[i].d, -1);
		}
		i++;
	}
}

int		closest_inter(t_ray ray, t_scene *s, t_vector *inter, t_vector *N)
{
	t_vector	interf;
	t_vector	Nf;
	int			i;
	int			final;
	float		t;
	float		tp;

	t = 1E99;
	final = -1;
	i = 0;
	while (s->objects[i].type != -1)
	{
		tp = inter_type(ray, s->objects[i], inter, N);
		if (tp < t)
		{
			t = tp;
			Nf = *N;
			interf = *inter;
			final = i;
		}
		i++;
	}
	*N = Nf;
	*inter = interf;
	return (final);
}