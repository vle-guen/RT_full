/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 08:50:25 by vle-guen          #+#    #+#             */
/*   Updated: 2016/06/14 12:35:07 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double	inter_hyperboloid(t_obj *obj, t_env *e)
{
	t_vec3d     eo;
	double      a;
	double      b;
	double      c;
	t_vec3d     ray_dir;

	ray_dir = (t_vec3d){e->ray_dir.x, e->ray_dir.y, e->ray_dir.z};
	eo = eye_or(e->ray_origin, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.x);
	rotate_y(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.y);
	rotate_z(&(ray_dir.x), &(ray_dir.y), &(ray_dir.z), -obj->rot.z);
	a = (pow(obj->coeff.y, 2) * pow(obj->coeff.z, 2) * pow(ray_dir.x, 2))
		+ (pow(obj->coeff.x, 2)	* pow(obj->coeff.z, 2) * pow(ray_dir.y, 2))
		+ (pow(obj->coeff.x, 2) * pow(obj->coeff.y, 2) * pow(ray_dir.z, 2));
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
	if (e->det < 0.0001)
		return (-1);
/*	else
	{
		printf("xc = %f, yx = %f, zc = %f\n", obj->pos.x, obj->pos.y, obj->pos.z);
		printf("a = %f, b = %f, c = %f\n", obj->coeff.x, obj->coeff.y, obj->coeff.z);
		printf("raydirx = %f, raydiry = %f, raydirz = %f\n", ray_dir.x, ray_dir.y, ray_dir.z);
		printf("rayorigx = %f, rayorigy = %f, rayorigz = %f\n", eo.x, eo.y, eo.z);
		printf("%f\n", e->det);
		}*/
	e->det = (-b - sqrt(e->det)) / (2 * a);
	if (e->det > 0)
		return (e->det);
	else
		return ((-b + sqrt(e->det)) / (2 * a));
}
