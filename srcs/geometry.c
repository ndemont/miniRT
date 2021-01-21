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

	rslt = sqrt((powf((v2.coord[0] - v1.coord[0]), 2) + powf((v2.coord[1] - v1.coord[1]), 2)) + powf((v2.coord[2] - v1.coord[2]), 2));
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

float		inter_sp(t_ray ray, t_object sp, t_vector *inter, t_vector *normal)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		t;
	float		t1;
	float		t2;
	int			i;

	i = 0;
	a = 1;
	t = 1E99;
	b = 2 * scalaire(ray.d, v_minus_v(ray.o, sp.o));
	c = get_norme_2(v_minus_v(ray.o, sp.o)) - (sp.diam * sp.diam);
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
			inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
			inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
			inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
			*normal = get_normalized(v_minus_v(*inter, sp.o));
		}
	}
	return (t);
}

float		inter_cy(t_ray ray, t_object cy, t_vector *inter, t_vector *N)
{
	float 		r;
	float 		m;
	float		t;
	t_vector	X;
	float		D;
	float		t1;

	t1 = -1;
	cy.d = get_normalized(cy.d);
	X = v_minus_v(cy.o,ray.o);
	X = get_normalized(X);
	r = cy.diam / 2;
	t = 0;
	inter->coord[0] =  powf(ray.d.coord[0], 2) + powf(ray.d.coord[1], 2);
	inter->coord[1] = 2 * ((ray.o.coord[0] * ray.d.coord[0]) + (ray.o.coord[1] * ray.d.coord[1]));
	inter->coord[2] = (ray.o.coord[0] * ray.o.coord[0]) + (ray.o.coord[1] * ray.o.coord[1]) - 1;

	D = powf(inter->coord[1], 2) - (4 * inter->coord[0] * inter->coord[2]);
	//printf("D = %f\n", D);
	if (D > 0)
	{
		t1 = ((-1 * inter->coord[1]) - sqrt(D)) / ((2 * inter->coord[0]) - 0.0001);
        if (t1 <= 0)
		{
        	t1 = ((sqrt(D) - inter->coord[1])) / ((2 * inter->coord[0]) - 0.0001);
        }
	}
	//inter->coord[0] = scalaire(ray.d, ray.d) - powf(scalaire(ray.d, tr.d), 2);
	//inter->coord[1] = (scalaire(ray.d, X) - (scalaire(ray.d, tr.d) * scalaire(X, tr.d))) * 2;
	//inter->coord[2] = powf(scalaire(X, X), 2) + (powf(scalaire(X, tr.d), 2)) - (r * r);
	//printf("intersection = %f/%f/%f\n", inter->coord[0], inter->coord[1], inter->coord[2]);
	m = (scalaire(ray.d, cy.d) * t) + scalaire(X, cy.d);
	*N = v_mult_i(cy.d, m);
	*N = v_minus_v(cy.o, *N);
	*N = v_minus_v(*inter, *N);
	*N = get_normalized(*N);
	if (t1 >= 0)
	{
		//printf("intersection = %f/%f/%f\n", inter->coord[0], inter->coord[1], inter->coord[2]);
		printf("t = %f\n", t1);
		return (t1);
	}
	else
		return (1E99);
}	


float		inter_tr(t_ray ray, t_object sp, t_vector *inter, t_vector *N)
{
	float		a;
	float		t;
	float		tf;
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
	tf = 1E99;
	final = -1;
	v1 = v_minus_v(sp.d, sp.o);
	v2 = v_minus_v(sp.p, sp.o);
	*N = v_produit_v(v1, v2);
	*N = get_normalized(*N);
	//*N = get_normalized(sp.d);
	//printf("normal = %f/%f/%f\n", N->coord[0], N->coord[1], N->coord[2]);
	v5 = v_minus_v(sp.p, ray.o);
	v3 = scalaire(v5, *N);
	v4 = scalaire(ray.d, *N);
	t = v3 / v4;
	//write(1, "test 00\n", 9);
	if (t >= 0)
	{
		inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
		inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
		inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
		u = v_minus_v(sp.d, sp.o);
		v = v_minus_v(sp.p, sp.o);
		w = v_minus_v(*inter, sp.o);
		// u = v_minus_v(sp.p1, sp.p2);
		// v = v_minus_v(sp.p3, sp.p2);
		// w = v_minus_v(*inter, sp.p2);
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
			tf = t;
	}
	//printf("tf = %f\n", tf);
	//write(1, "test 01\n", 9);
	return (tf);
}

float		inter_sq(t_ray ray, t_object sq, t_vector *inter, t_vector *N)
{
	float		t;
	t_vector	v;
	int			count;

	*N = sq.d;
	*N = get_normalized(*N);
	count = 0;
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *N) / scalaire(ray.d, *N);
	if (t >= 0)
	{
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
		if (inter->coord[0] <= sq.o.coord[0] + (sq.h / 2) && inter->coord[0] >= sq.o.coord[0] - (sq.h / 2))
			count++;
		if (inter->coord[1] <= sq.o.coord[1] + (sq.h / 2) && inter->coord[1] >= sq.o.coord[1] - (sq.h / 2))
			count++;
		if (inter->coord[2] <= sq.o.coord[2] + (sq.h / 2) && inter->coord[2] >= sq.o.coord[2] - (sq.h / 2))
			count++;
		if (count != 3)
			t = 1E99;
	}
	else 
		t = 1E99;
	return (t);
}

float		inter_pl(t_ray ray, t_object sq, t_vector *inter, t_vector *N)
{
	float		t;
	t_vector	v;
	
	*N = sq.d;
	*N = get_normalized(*N);
    //printf("Normal1 = %f/%f/%f\n", N[0].coord[0], N[0].coord[1], N[0].coord[2]);
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *N) / scalaire(ray.d, *N);
    //printf("t = %f\n", t);
	if (t >= 0)
		*inter = v_plus_v(ray.o, v_mult_i(ray.d, t));
	else 
		t = 1E99;
	return (t);
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
	float		scal1;
	float		scal2;
	t_vector	normal;
	float		t;
	int 		i;

	i = 0;
	while (s->objects[i].type != -1)
	{
		ray.o = s->cameras[0].o;
		ray.d = s->cameras[0].c;
		normalize(&ray.d);
		if (s->objects[i].type == 6 || s->objects[i].type == 12)
		{
			normal = s->objects[i].d;
			printf("\n\nnormal 1 = %f/%f/%f\n", normal.coord[0], normal.coord[1], normal.coord[2]);
			normal = get_normalized(normal);
			scal1 = scalaire(v_minus_v(s->objects[i].o, ray.o), normal);
			scal2 = scalaire(ray.d, normal);
			printf("NUMERO %d\nscal1  = %f\nscal2 = %f\nt = %f\n", i, scal1, scal2, t);
			t = scal1 / scal2;
			if (scal1 > 0)
			{
				s->objects[i].d = v_mult_i(s->objects[i].d, -1);
				printf("switch\n");
			}
			printf("normal 2 = %f/%f/%f\n", s->objects[i].d.coord[0], s->objects[i].d.coord[1], s->objects[i].d.coord[2]);
		}
		if (s->objects[i].type == 20)
		{
			//s->objects[i].d = v_minus_v(s->objects[i].p1, s->objects[i].p2);
			//s->objects[i].d = v_produit_v(s->objects[i].d, v_minus_v(s->objects[i].p3, s->objects[i].p2));
			//printf("normal = %f/%f/%f\n", normal.coord[0], normal.coord[1], normal.coord[2]);
			normal = get_normalized(s->objects[i].d);
			printf("normal = %f/%f/%f\n", normal.coord[0], normal.coord[1], normal.coord[2]);
			//scal1 = scalaire(v_minus_v(s->objects[i].p1, ray.o), normal);
			scal2 = scalaire(ray.d, normal);
			t = scal1 / scal2;
			if (scal1 > 0)
				s->objects[i].d = v_mult_i(normal, -1);
			else 
				s->objects[i].d = get_normalized(s->objects[i].d);
			printf("NUMERO %d\nscal1  = %f\nscal2 = %f\nt = %f\n", i, scal1, scal2, t);
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