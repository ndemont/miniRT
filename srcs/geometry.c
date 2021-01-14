#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <geometry.h>

float		scalaire(t_vector v1, t_vector v2)
{
	float rslt;

	rslt = (v1.coord[0] * v2.coord[0]) + (v1.coord[1] * v2.coord[1]) + (v1.coord[2] * v2.coord[2]);
	return (rslt);
}

float		distance(t_vector v1, t_vector v2)
{
	float rslt;

	rslt = sqrt((powf((v1.coord[0] + v2.coord[0]), 2) + powf((v1.coord[1] + v2.coord[1]), 2)) + powf((v1.coord[2] + v2.coord[2]), 2));
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
	v3.coord[2] = v1.coord[0] * v2.coord[1] - v1.coord[2] * v2.coord[0];
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

double		inter3(t_ray ray, t_object *sp, t_vector *inter, t_vector *normal)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		t;
	double		tf;
	float		t1;
	float		t2;
	int			i;

	i = 0;
	a = 1;
	tf = 1E99;
	while (sp[i].type != -1)
	{
		b = 2 * scalaire(ray.d, v_minus_v(ray.o, sp[i].o));
		c = get_norme_2(v_minus_v(ray.o, sp[i].o)) - (sp[i].diam * sp[i].diam);
		delta = (b * b) - (4 * a * c);
		if (delta >= 0)
		{
			t1 = (-b - (sqrt(delta))) / (2 * a);
			t2 = (-b + (sqrt(delta))) / (2 * a);
 			if (t2 >= 0)
			{
				if (t1 > 0)
					t = t1;
				else 
					t = t2;
				if (t < tf)
				{
					tf = t;
					if (i)
					{
						//printf(" i = %d\n", i);
						//printf(" color R = %f\n", sp[i].c.coord[0]);
					}
					inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
					inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
					inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
					*normal = get_normalized(v_minus_v(*inter, sp[i].o));
				}
			}
		}
		i++;
	}
	return (tf);
}


int		inter2(t_ray ray, t_object *sp, t_vector *inter, t_vector *normal)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		t;
	float		tf;
	float		t1;
	float		t2;
	int			i;
	int			final;

	i = 0;
	a = 1;
	tf = 1E99;
	final = -1;
	while (sp[i].type != -1)
	{
		b = 2 * scalaire(ray.d, v_minus_v(ray.o, sp[i].o));
		c = get_norme_2(v_minus_v(ray.o, sp[i].o)) - (sp[i].diam * sp[i].diam);
		delta = (b * b) - (4 * a * c);
		if (delta >= 0)
		{
			t1 = (-b - (sqrt(delta))) / (2 * a);
			t2 = (-b + (sqrt(delta))) / (2 * a);
 			if (t2 >= 0)
			{
				if (t1 > 0)
					t = t1;
				else 
					t = t2;
				if (t < tf)
				{
					tf = t;
					final = i;
					inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
					inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
					inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
					*normal = get_normalized(v_minus_v(*inter, sp[i].o));
				}
			}
		}
		i++;
	}
	return (final);
}

int		inter_triangle(t_ray ray, t_object *sp, t_vector *inter, t_vector *N)
{
	float		a;
	float		t;
	int			i;
	int			final;
	t_vector	v1;
	t_vector	v2;
	t_vector	v5;
	float		v3;
	float		v4;
	t_vector 	u;
	t_vector 	v;
	t_vector 	w;
	double		m11;
	double		m12;
	double		m22;
	double		detm;
	double		b11;
	double		b21;
	double		beta;
	double		detb;
	double		g12;
	double		g22;
	double		detg;
	double		gamma;
	double		alpha;

	i = 0;
	a = 1;
	final = -1;
	while (sp[i].type != -1)
	{
		v1 = v_minus_v(sp[i].d, sp[i].o);
		v2 = v_minus_v(sp[i].p, sp[i].o);
		*N = v_produit_v(v1, v2);
		*N = get_normalized(*N);
		v5 = v_minus_v(sp[i].p, ray.o);
		v3 = scalaire(v5, *N);
		v4 = scalaire(ray.d, *N);
		t = v3 / v4;
		f("D : a = %f - b = %f, c = %f\n", sp[i].d.coord[0], sp[i].d.coord[1], sp[i].d.coord[2]);

		if (t >= 0)
		{
			inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
			inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
			inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
			u = v_minus_v(sp[i].d, sp[i].o);
			v = v_minus_v(sp[i].p, sp[i].o);
			w = v_minus_v(*inter, sp[i].o);
			m11 = get_norme_2(u);
			m12 = scalaire(u, v);
			m22 = get_norme_2(v);
			detm = (m11) * (m22) - (m12 * m12);
			b11 = scalaire(w, u);
			b21 = scalaire(w, v);
			detb = (b11) * (m22) - (b21 * m12);
			beta = detb / detm;
			g12 = b11;
			g22 = b21;
			detg = (m11 * g22) - (m12 * g12);
			gamma = detg / detm;
			alpha = 1 - beta - gamma;
			if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1)
			{
				final = i;
			}
		}
		i++;
	}
	return (final);
}