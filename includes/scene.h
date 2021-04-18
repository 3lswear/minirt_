#ifndef SCENE_H
# define SCENE_H

typedef struct	s_scene
{
	t_cam 		*cams;
	//TODO: add generic type that holds all types of figures
	t_sphere	*sphere;
	float		width;
	float 		height;

}				t_scene;


t_scene *new_scene(t_cam *cam, t_sphere *sphere);

#endif
