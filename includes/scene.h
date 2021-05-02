#ifndef SCENE_H
# define SCENE_H

typedef struct s_scene
{
	double		width;
	double		height;
	t_color		ambient;
	double		amb_intensity;
	t_list		*cams;
	t_list		*objects;
	t_list		*lights;

}				t_scene;

t_scene	*new_scene(t_cam *cam);

#endif
