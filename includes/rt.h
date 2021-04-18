#ifndef RT_H
# define RT_H

typedef struct s_viewport
{
	float width;
	float height;
	float x_pixel;
	float y_pixel;
	
}				t_view;

t_view *get_viewport(float width, float height, float fov);

#endif
