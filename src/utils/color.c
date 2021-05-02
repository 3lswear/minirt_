#include "minirt.h"

/* t_color	argb_color(int r, int g, int b) */
/* { */
/* 	int	color; */

/* 	if (r > 255) */
/* 		r = 255; */
/* 	if (g > 255) */
/* 		g = 255; */
/* 	if (b > 255) */
/* 		b = 255; */
/* 	color = 0; */
/* 	color += r; */
/* 	color = color << 8; */
/* 	color += g; */
/* 	color = color << 8; */
/* 	color += b; */
/* 	return (color); */
/* } */

/* t_color	c_add(t_color color1, int color2) */
/* { */
/* 	int	result; */
/* 	int	channel; */

/* 	channel = (color1 & R_MASK) + (color2 & R_MASK); */
/* 	if (channel > R_MASK) */
/* 		channel = R_MASK; */
/* 	result = channel; */
/* 	channel = (color1 & G_MASK) + (color2 & G_MASK); */
/* 	if (channel > G_MASK) */
/* 		channel = G_MASK; */
/* 	result += channel; */
/* 	channel = (color1 & B_MASK) + (color2 & B_MASK); */
/* 	if (channel > B_MASK) */
/* 		channel = B_MASK; */
/* 	result += channel; */
/* 	return (result); */
/* } */

/* t_color	c_mul_scalar(t_color color, double mul) */
/* { */
/* 	int	result; */

/* 	if (mul > 1) */
/* 		return (color); */
/* 	result = (color >> 16) * mul; */
/* 	result = result << 8; */
/* 	result += ((color & G_MASK) >> 8) * mul; */
/* 	result = result << 8; */
/* 	result += (color & B_MASK) * mul; */
/* 	return (result); */
/* } */

/* t_color	c_mul(t_color color1, t_color color2) */
/* { */
/* 	t_color	result; */
/* 	double	channel; */

/* 	color1 = color1 & WHITE; */
/* 	color2 = color2 & WHITE; */
/* 	channel = idiv((color1 >> 16), 255) * idiv(color2 >> 16, 255); */
/* 	result = channel * 255; */
/* 	result = result << 8; */
/* 	channel = idiv((color1 & G_MASK) >> 8, 255) */
/* 		* idiv((color2 & G_MASK) >> 8, 255); */
/* 	result += channel * 255; */
/* 	result = result << 8; */
/* 	channel = idiv((color1 & B_MASK), 255) * idiv(color2 & B_MASK, 255); */
/* 	result += channel * 255; */
/* 	return (result); */
/* } */

t_color new_color(int r, int g, int b)
{
	t_color result;
	result.r = r / 255.0;
	result.g = g / 255.0;
	result.b = b / 255.0;
	return (result);
}

int argb_color(t_color color)
{
	int result;
	int channel;

	channel = color.r * 0xFF;
	if (channel > 0xFF)
		channel = 0xFF;
	result = channel;
	result = result << 8;
	channel = color.g * 0xFF;
	if (channel > 0xFF)
		channel = 0xFF;
	result += channel;
	result = result << 8;
	channel = color.b * 0xFF;
	if (channel > 0xFF)
		channel = 0xFF;
	result += channel;
	return (result);
}

t_color c_add(t_color color1, t_color color2)
{
	t_color result;
	result.r = color1.r + color2.r;
	/* if (result.r > 1) */
	/* 	result.r = 1; */
	result.g = color1.g + color2.g;
	/* if (result.g > 1) */
	/* 	result.g = 1; */
	result.b = color1.b + color2.b;
	/* if (result.b > 1) */
	/* 	result.b = 1; */
	return (result);
}

t_color c_mul_scalar(t_color color, double mul)
{
	t_color result;
	result.r = color.r * mul;
	if (result.r > 1)
		result.r = 1;
	result.g = color.g * mul;
	if (result.g > 1)
		result.g = 1;
	result.b = color.b * mul;
	if (result.b > 1)
		result.b = 1;
	return (result);
}

t_color c_mul(t_color color1, t_color color2)
{
	t_color result;

	result.r = color1.r * color2.r;
	if (result.r > 1)
		result.r = 1;
	result.g = color1.g * color2.g;
	if (result.g > 1)
		result.g = 1;
	result.b = color1.b * color2.b;
	if (result.b > 1)
		result.b = 1;
	return (result);
}
