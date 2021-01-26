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

float		inter_cy2(t_ray ray, t_object cy, t_vector *inter, t_vector *N)
{
	float 		r;
	float		t;
	t_vector 	va;
	t_vector	v;
	t_vector	rao;
	t_vector 	s;
	t_vector	rorcy;
	float		D;
	float		t1;
	float		t2;
	float		a;
	float		b;
	float		c;
	t_vector	C;
	float		d;

	r = cy.diam / 2;
	t = -1;
	v = ray.d;
	s = cy.d;
	rorcy = v_minus_v(ray.o, cy.o);
	rao = v_produit_v(v_produit_v(s, rorcy), s);
	va = v_produit_v(v_produit_v(s, v), s);
	a = scalaire(va, va);
	b = scalaire(v_mult_i(rao, 2), va);
	c = scalaire(rao, rao) - powf(r, 2);
	D = (b * b) - (4 * a * c);
	if (D >= 0)
	{
		t1 = (-b - (sqrt(D))) / (2 * a);
		t2 = (-b + (sqrt(D))) / (2 * a);
 		if (t1 >= 0)
		{
			if (t1 > 0)
			{
				t = t1;
				inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
				inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
				inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
				//printf("intersection = %f/%f/%f\n", inter->coord[0], inter->coord[1], inter->coord[2]);
				d = scalaire(v_minus_v(*inter, cy.o), cy.d);
				if (d < cy.h && d > 0)
				{
					C = v_plus_v(cy.o, v_mult_i(cy.d, d));
					*N = get_normalized(v_minus_v(*inter, C));
					//printf("N = %f/%f/%f\n", N->coord[0], N->coord[1], N->coord[2]);
				}
				else 
					t = -1;
			}
			if (t == -1)
			{
				t = t2;
				inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
				inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
				inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
				//printf("intersection = %f/%f/%f\n", inter->coord[0], inter->coord[1], inter->coord[2]);
				d = scalaire(v_minus_v(*inter, cy.o), cy.d);
				if (d < cy.h && d > 0)
				{
					C = v_plus_v(cy.o, v_mult_i(cy.d, d));
					*N = get_normalized(v_minus_v(*inter, C));
				}
				else
					t = -1;
			}
		}
	}
	if (t == -1)
		t = 1E99;
	return (t);
}	


float		inter_cy(t_ray ray, t_object cy, t_vector *inter, t_vector *N)
{
	float 		r;
	float		t;
	t_vector 	va;
	t_vector	v;
	t_vector	rao;
	t_vector 	s;
	t_vector	rorcy;
	float		D;
	float		t1;
	float		t2;
	float		a;
	float		b;
	float		c;
	t_vector	C;
	float		d;

	r = cy.diam / 2;
	t = -1;
	v = ray.d;
	t2 = 0;
	s = get_normalized(cy.d);
	rorcy = v_minus_v(ray.o, cy.o);
	rao = v_produit_v(v_produit_v(s, rorcy), s);
	va = v_produit_v(v_produit_v(s, v), s);
	a = scalaire(va, va);
	b = scalaire(v_mult_i(rao, 2), va);
	c = scalaire(rao, rao) - powf(r, 2);
	D = (b * b) - (4 * a * c);
	if (D >= 0)
	{
		t1 = (-b - (sqrt(D))) / (2 * a);
		t2 = (-b + (sqrt(D))) / (2 * a);
 		if (t2 >= 0)
		{
			if (t1 > 0)
			{
				t = t1;
				inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
				inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
				inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
				//printf("intersection = %f/%f/%f\n", inter->coord[0], inter->coord[1], inter->coord[2]);
				d = scalaire(v_minus_v(*inter, cy.o), s);
				if (d < cy.h / 2 && d > -cy.h / 2) //&& d > 0)
				{
				// 	C = v_plus_v(cy.o, v_mult_i(cy.d, d));
				// 	*N = get_normalized(v_minus_v(*inter, C));
				// 	// if (scalaire(*N, ray.d) > 0)
				// 	// {
					//if (d >= 0)
						//cy.d = v_mult_i(cy.d, -1);
					C = v_plus_v(cy.o, v_mult_i(s, d));
					*N = get_normalized(v_minus_v(*inter, C));

				// 	printf("N = %f/%f/%f\n", N->coord[0], N->coord[1], N->coord[2]);
				}
				else 
					t = -1;
			}
			if (t == -1)
			{
				t = t2;
				inter->coord[0] = ray.o.coord[0] + (t * ray.d.coord[0]);
				inter->coord[1] = ray.o.coord[1] + (t * ray.d.coord[1]);
				inter->coord[2] = ray.o.coord[2] + (t * ray.d.coord[2]);
				//printf("intersection = %f/%f/%f\n", inter->coord[0], inter->coord[1], inter->coord[2]);
				d = scalaire(v_minus_v(*inter, cy.o), s);
				if (d < cy.h / 2 && d > -cy.h / 2) //&& d > 0)
				{
				// 	C = v_plus_v(cy.o, v_mult_i(cy.d, d));
				// 	*N = get_normalized(v_minus_v(*inter, C));
				// 	// if (scalaire(*N, ray.d) > 0)
				// 	// {
					//if (d >= 0)
						//cy.d = v_mult_i(cy.d, -1);
					C = v_plus_v(cy.o, v_mult_i(s, d));
					*N = get_normalized(v_minus_v(*inter, C));

				// 	printf("N = %f/%f/%f\n", N->coord[0], N->coord[1], N->coord[2]);
				}
				else
					t = -1;
			}
		}
	}
	if (t == -1)
		t = 1E99;
	if (scalaire(*N, ray.d) > 0)
		*N = v_mult_i(*N, -1);
	return (t);
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
	v = v_minus_v(sq.o, ray.o);
	t = scalaire(v, *N) / scalaire(ray.d, *N);
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

float		inter_type2(t_ray ray, t_object o, t_vector *inter, t_vector *N)
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
	t_vector	normal;
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
			normal = get_normalized(normal);
			scal1 = scalaire(v_minus_v(s->objects[i].o, ray.o), normal);
			if (scal1 > 0)
			{
				s->objects[i].d = v_mult_i(s->objects[i].d, -1);
				printf("switch\n");
			}
			printf("normal 2 = %f/%f/%f\n", s->objects[i].d.coord[0], s->objects[i].d.coord[1], s->objects[i].d.coord[2]);
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