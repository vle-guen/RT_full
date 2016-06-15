/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:59:29 by avella            #+#    #+#             */
/*   Updated: 2016/06/15 13:08:12 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

t_vec3d		give_vec(t_obj *obj, t_env *e)
{
	t_vec3d my_vec;
	//rotation normal plan
	//rotate en negatif pour afficher dans plan
	my_vec = (t_vec3d){obj->rot.x, obj->rot.y,obj->rot.z};
	if (obj->type == 1)
	  my_vec = a_moins_b(&(e->position), &obj->pos);
	else if (obj->type == 2 || obj->type == 3)
	{
		my_vec.x = e->position.x - obj->pos.x;
		my_vec.y = e->position.y - obj->pos.y;;
		my_vec.z = e->position.z - obj->pos.z;
	}
	else if(obj->type == 4)
	  {
	    //	    my_vec = e->effect.vec;
	    my_vec.x = e->position.x - -10;//e->effect.vec.x;//-10;
	    my_vec.y = e->position.y - 5;//e->effect.vec.y;//5;
	    my_vec.z = e->position.z - -20;// e->effect.vec.z;//-20;
	  }
	else if (obj->type == 5)
	{
		my_vec.x = obj->normale.x;
		my_vec.y = obj->normale.y;
		my_vec.z = obj->normale.z;
	}
	ajust(&my_vec);
	return (my_vec);
}

t_vec3d		lambert_alg(t_obj *obj, t_env *e)
{
	t_vec3d		form;
	t_vec3d		light;
	double		value;
	double		d;

	light = a_moins_b(&obj->pos, &(e->position));
	ajust(&light);
	d = sqrt((e->position.x - obj->pos.x) * (e->position.x - obj->pos.x) +
			(e->position.y - obj->pos.y) * (e->position.y - obj->pos.y) +
			(e->position.z - obj->pos.z) * (e->position.z - obj->pos.z));
	d = lim(sqrt(1 / (d * (1.0 - obj->intens))), 0, 1);
	value = lim(dot_product(&(e->effect.vec), &light), 0, 1);
	if (e->effect.vec.x == 0 && e->effect.vec.y == 1 && e->effect.vec.z == 0)
		value = 1;
	form = mult_value(&obj->color, value);
	form = mult_value(&form, obj->intens);
	form = mult_value(&form, d);
	return (form);
}

t_vec3d		my_light(t_env *e)
{
	t_obj		*obj;
	t_vec3d		light;
	t_vec3d		my_light;

	obj = e->obj;
	light = (t_vec3d){0, 0, 0};
	while (obj)
	{
		if (obj->type == 8)
		{
			my_light = lambert_alg(obj, e);
			light = plus(&light, &my_light);
		}
		obj = obj->next;
	}
	light = mult_value(&light, e->nl);
	limit_for_vec(&light, 0.0, 1.0);
	return (light);
}

double		phong_alg(t_obj *obj, t_env *e)
{
	double		form;
	t_vec3d		calc;
	t_vec3d		light;
	double		keep;
	double		keep2;

	keep = dot_product(&(e->effect.vec), &(e->ray_dir));
	calc.x = e->ray_dir.x - 2 * keep * e->effect.vec.x;
	calc.y = e->ray_dir.y - 2 * keep * e->effect.vec.y;
	calc.z = e->ray_dir.z - 2 * keep * e->effect.vec.z;
	light = a_moins_b(&obj->pos, &(e->position));
	ajust(&light);
	ajust(&calc);
	keep2 = pow(lim(dot_product(&calc, &light), 0, 1), 20);
	form = lim(keep2, 0, 1);
	form *= pow(obj->intens, 0.5);
	return (form);
}

t_vec3d		light_effect(t_env *e)
{
	t_obj	*obj;
	t_vec3d	form;
	double	val;

	obj = e->obj;
	form = (t_vec3d){0, 0, 0};
	while (obj)
	{
		if (obj->type == 8)
		{
			val = phong_alg(obj, e);
			form.x = form.x + val;
			form.y = form.y + val;
			form.z = form.z + val;
		}
		obj = obj->next;
	}
	limit_for_vec(&form, 0, 1);
	return (form);
}
