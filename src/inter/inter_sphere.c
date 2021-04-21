#include "minirt.h"

int argb_color(unsigned char r, unsigned char g, unsigned char b)
{
	int color;
	color = 0;
	color += r;
	color = color << 8;
	color += g;
	color = color << 8;
	color+= b;
	/* printf("color is %X\n", color); */
	return (color);

}

int inter_objects(t_cam *cam, t_vec *ray, t_list *objs)
{
	char *string;
	char **split;
	char *id;
	int color;
	t_sphere *sphere;

	color = -1;
	while (objs)
	{
		id = ((char **)(objs->data))[0];
		/* printf("id =>%s\n", id); */
		if (!ft_strncmp(id, "sp", ft_strlen(id)))
		{
			string = ((char **)(objs->data))[1];
			split = ft_split(string, ',');
			string = ((char **)(objs->data))[2];
			sphere = new_sphere(
					v_new(ft_atoi(split[0]),
						ft_atoi(split[1]),
						ft_atoi(split[2])),
					ft_atoi(string));
			string = ((char **)(objs->data))[3];
			split = ft_split(string, ',');
			sphere->color = argb_color(
				ft_atoi(split[0]),
				ft_atoi(split[1]),
				ft_atoi(split[2]));
			if (inter_sphere(cam, ray, sphere))
				color = sphere->color;
		}
		objs = objs->next;
	}
	return (color);
}

int inter_sphere(t_cam *cam, t_vec *ray, t_sphere *sphere)
{
	float b;
	float c;
	float discr;
	float hit1;
	float hit2;
	t_vec *cam2sphere;

	hit1 = 0;
	hit2 = 0;

	/* printf("sphere->radius = %f\n", sphere->radius); */
	cam2sphere = v_sub(cam->origin, sphere->center);
	b = 2 * v_dot_product(cam2sphere, ray);
	c = v_dot_product(cam2sphere, cam2sphere) - (pow(sphere->radius, 2));
	discr = (b * b) - (4 * c);
	/* free(cam2sphere); */
	if (discr < 0)
		return (0);
	hit1 = (-b - sqrt(discr)) / 2;
	hit2 = (-b + sqrt(discr)) / 2;
	//choose which distance to return
	/* if ((hit1 * hit2) > 0) */
	if (hit1 > 0)
		return (1);
	else
		return (0);
}
