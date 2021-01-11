#include "minirt.h"

float	ft_atof(const char *str)
{
	int		i;
	float	nb;
	float	sign;
    float   coma;

	i = 0;
	nb = 0;
	sign = 1;
    coma = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
    if (str[i] == '.')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
	    {
		    nb = nb + ((coma * 0.1) * (str[i] - 48));
		    i++;
    	}
    }
	return (nb * sign);
}