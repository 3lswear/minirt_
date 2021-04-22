#ifndef SCENE_H
# define SCENE_H


typedef struct	s_scene
{
	t_cam 		*cams;
	//TODO: add generic type that holds all types of figures
	t_list		*objs;
	t_list 		*spheres;
	t_list		*planes;
	t_light		*light;
	float		width;
	float 		height;
	int			ambient;

}				t_scene;


t_scene *new_scene(t_cam *cam, t_list *obj_list);

#endif
