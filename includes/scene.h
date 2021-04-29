#ifndef SCENE_H
# define SCENE_H


typedef struct	s_scene
{
	t_cam 		*cams;
	t_list 		*spheres;
	t_list		*planes;

	t_list	*objects;

	t_list		*lights;
	double		width;
	double 		height;
	t_color		ambient;
	double		amb_intensity;

}				t_scene;


t_scene *new_scene(t_cam *cam);

#endif
