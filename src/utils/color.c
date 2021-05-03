#include "minirt.h"

t_color	new_color(int r, int g, int b)
{
	t_color	result;

	result.r = r / 255.0;
	result.g = g / 255.0;
	result.b = b / 255.0;
	return (result);
}

int	argb_color(t_color color)
{
	int	result;
	int	channel;

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

t_color	c_add(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

t_color	c_mul_scalar(t_color color, double mul)
{
	t_color	result;

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

t_color	c_mul(t_color color1, t_color color2)
{
	t_color	result;

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
