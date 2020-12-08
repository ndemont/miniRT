#ifndef SCENE_H
# define SCENE_H

typedef	struct	s_R
{
	int		x;
	int		y;
}				t_R;

typedef	struct	s_point
{
	int		x;
	int		y;
	int		z;
}				t_point;

typedef	struct	s_A
{
	float	*ratio[2];
	int		*rgb[3];
}				t_A;

typedef	struct	s_c
{
	float	*pov[3];
	float	*v[2];
	int		*fov[2];
}				t_c;

typedef	struct	s_l
{
	float	*p[3];
	float	*ratio[2];
	int		*rgb[3];
}				t_l;

typedef	struct	s_sp
{
	float	*p[3];
	float	r;
	int		*rgb[3];
}				t_sp;

typedef	struct	s_pl
{
	float	*p[3];
	float	*v[2];
	int		*rgb[3];
}				t_pl;

typedef	struct	s_sq
{
	float	*p[3];
	float	*v[2];
	float	h;
	int		*rgb[3];
}				t_sq;

typedef	struct	s_cy
{
	float	*p[3];
	float	*v[2];
	float	h;
	float	d;
	int		*rgb[3];
}				t_cy;

typedef	struct	s_tr
{
	float	*p1[3];
	float	*p2[3];
	float	*p3[3];
	int		*rgb[3];
}				t_tr;

#endif