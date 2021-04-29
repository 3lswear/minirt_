#include "minirt.h"

void iter_cams(t_scene *scene, t_win *window)
{
	t_list *current;
	t_cam *cam;

	current = scene->cams;
	while (current)
	{
		cam = current->data;
		/* transform scene maybe */
		trace(window, scene, cam);
		/* loop and hook to switch to the next one */
		printf("switching to the next cam!!!\n");
		current = current->next;
	}

}
