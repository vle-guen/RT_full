/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 08:50:25 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/15 15:19:26 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double		get_norme(t_vec3d a)
{
	double		x;

	x = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	a.norme = sqrt(x);
	return (a.norme);
}

t_vec3d		normalize(t_vec3d a)
{
	a.x = a.x / a.norme;
	a.y = a.y / a.norme;
	a.z = a.z / a.norme;
	return (a);
}

/*double	inter_hyperboloid(t_obj *obj, t_env *e)
{
	t_vec3d     eo;
	double      a;
	double      b;
	double      c;
	t_vec3d     ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	ray_dir.norme = get_norme(ray_dir);
	ray_dir = normalize(ray_dir);
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
*	a = (pow(obj->coeff.y, 2) * pow(obj->coeff.z, 2) * pow(ray_dir.x, 2))
		+ (pow(obj->coeff.x, 2)	* pow(obj->coeff.z, 2) * pow(ray_dir.y, 2))
		- (pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * pow(ray_dir.z, 2));
	b = (2 * pow(obj->coeff.y, 2) * pow(obj->coeff.z, 2) * eo.x * ray_dir.x)
		+ (2 * pow(obj->coeff.x, 2) * pow(obj->coeff.z, 2) * eo.y * ray_dir.y)
		+ (2 * pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * eo.z * ray_dir.z)
		- (2 * obj->pos.x * pow(obj->coeff.y, 2) * pow(obj->coeff.z, 2)
		* ray_dir.x) - (2 * obj->pos.y * pow(obj->coeff.x, 2)
		* pow(obj->coeff.z, 2) * ray_dir.y)	- (2 * obj->pos.z
		* pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * ray_dir.z);
	c = (pow(obj->coeff.y, 2) * pow(obj->coeff.z, 2) * pow(eo.x, 2))
		+ (pow(obj->coeff.x, 2) * pow(obj->coeff.z, 2) * pow(eo.y, 2))
		+ (pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * pow(eo.z, 2))
		- (2 * obj->coeff.y * pow(obj->coeff.z, 2) * pow(obj->pos.x, 2)
		* eo.x)	- (2 * obj->coeff.z * pow(obj->coeff.x, 2)
		* pow(obj->pos.y, 2) * eo.y) - (2 * obj->coeff.y
		* pow(obj->coeff.x, 2) * pow(obj->pos.y, 2) * eo.z)
		+ (pow(obj->coeff.y, 2) * pow(obj->coeff.z, 2) * obj->pos.x)
		+ (pow(obj->coeff.x, 2) * pow(obj->coeff.z, 2) * obj->pos.y)
		+ (pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * obj->pos.z)
		- (pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * pow(obj->coeff.y, 2));
	e->det = b * b - 4 * a * c;
	if (e->det == 0.f)
		return (-b / (2 * a));
	if (e->det < 0.0001)
		return (-1);
	e->det = (-b - sqrt(e->det)) / (2 * a);
	if (e->det > 0)
		return (e->det);
	else
		return ((-b + sqrt(e->det)) / (2 * a));
}*/

t_vec3d		get_impact(t_vec3d eo, double delta, t_vec3d ray_dir)
{
	t_vec3d		result;

	result.x = eo.x + delta * ray_dir.x;
	result.y = eo.y + delta * ray_dir.y;
	result.z = eo.z + delta * ray_dir.z;
	return (result);
}

t_vec3d		get_normale_hyper(t_vec3d impact, double k)
{
	t_vec3d		result;

	result.x = impact.x * 2;
	result.y = impact.y * (-2) * k;
	result.z = impact.z * 2;
	return (result);
}

double		inter_hyperboloid(t_obj *obj, t_env *e)
{
	t_vec3d     eo;
	double      a;
	double      b;
	double      c;
	t_vec3d     ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	ray_dir.norme = get_norme(ray_dir);
	ray_dir = normalize(ray_dir);
	eo = eye_or(e->ray_origin, obj->pos);
	obj->k = (pow(obj->size, 2) - 1) / pow(obj->ref, 2);
	a = pow(ray_dir.x, 2) + pow(ray_dir.z, 2) - obj->k * pow(ray_dir.y, 2);
	b = 2 * ((eo.x * ray_dir.x) + (eo.z * ray_dir.z)
	- (obj->k * eo.y * ray_dir.y));
	c = pow(eo.x, 2) + pow(eo.z, 2) + (obj->k * pow(eo.y, 2)) - 1;
	e->det = b * b - 4 * a * c;
	if (e->det == 0.f)
	{
		obj->impact_pt = get_impact(eo, e->det, ray_dir);
		obj->normale = get_normale_hyper(obj->impact_pt, obj->k);
		return (-b / (2 * a));
	}
	if (e->det < 0.0001)
		return (-1);
	e->det = (-b - sqrt(e->det)) / (2 * a);
	if (e->det > 0)
	{
		obj->impact_pt = get_impact(eo, e->det, ray_dir);
		obj->normale = get_normale_hyper(obj->impact_pt, obj->k);
		return (e->det);
	}
	else
	{
		e->det = (-b + sqrt(e->det)) / (2 * a);
		obj->impact_pt = get_impact(eo, e->det, ray_dir);
		obj->normale = get_normale_hyper(obj->impact_pt, obj->k);
		return (e->det);
	}
}
