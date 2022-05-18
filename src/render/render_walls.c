/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:20:12 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 13:08:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "core.h"
#include "render.h"

float			shoot_ray(t_vec2 ray, t_vec2 pos, t_ivec2 map_pos);
static void		shoot_rays(float ray_angle, float ray_angle_base);
static void		print_vec(const char *msg, t_vec2 vec);

static t_vec2 calculate_lengths(t_vec2 *ray);
static t_ivec2 calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos);
static int		get_map_type(int64_t x, int64_t y);

void	render_walls(int fov)
{
	float	ray_angle;
	float	ray_angle_base;
	static int	val;

	get_player()->pos = vec2(60, 60);
	ray_angle = (float)WIN_W / (float)fov;
	ray_angle_base = sin(val);//((float)PI - ((float)fov / 180.0f)) / 2.0f;
	shoot_rays(ray_angle, ray_angle_base);
	val++;
}

static void	shoot_rays(float ray_angle, float ray_angle_base)
{
	size_t	i;
	t_vec2	pos;
	t_ivec2	map_pos;

	pos = get_player()->pos;
	vec2_divf(&pos, CELL_WIDTH);
	map_pos.x = (int)pos.x;
	map_pos.y = (int)pos.y;
	i = 0;
	while (i < WIN_W)
	{
		shoot_ray(vec2(cosf(ray_angle_base), sinf(ray_angle_base)), pos, map_pos);
		ray_angle_base += ray_angle;
		i++;
	}
}

float	shoot_ray(t_vec2 ray, t_vec2 pos, t_ivec2 map_pos)
{
	t_ivec2	step;
	t_vec2	lengths;
	t_vec2	dists;
	t_bool	hit;
	int		side;

	lengths = calculate_lengths(&ray);
	step = calculate_step_dists(&ray, &dists, pos, map_pos);
	vec2_multv2(&dists, lengths);
	//print_vec("ray:", ray);
	//print_vec("pos:", pos);
	//print_vec("dists:", dists);
	//print_vec("lengths:", lengths);
	hit = FALSE;
	side = 0;
	while (!hit && dists.x < RAY_LENGTH && dists.y < RAY_LENGTH)
	{
		if (dists.x < dists.y)
		{
			dists.x += lengths.x;
			map_pos.x += step.x;
			side = SIDE_X;
		}
		else
		{
			dists.y += lengths.y;
			map_pos.y += step.y;
			side = SIDE_Y;
		}
		if (get_map_type(map_pos.x, map_pos.y) == WALL)
			hit = TRUE;
	}
	if (side == SIDE_X)
		return (dists.x);
	return (dists.y);
}

static t_vec2 calculate_lengths(t_vec2 *ray)
{
	t_vec2	lengths;

	if (ray->x == 0)
		lengths.x = MAXFLOAT;
	else
		lengths.x = 1.0f / ray->x;
	if (ray->y == 0)
		lengths.y = MAXFLOAT;
	else
		lengths.y = 1.0f / ray->y;
	return (lengths);
}

static t_ivec2 calculate_step_dists(t_vec2 *ray, t_vec2 *dists, t_vec2 pos, t_ivec2 map_pos)
{
	t_ivec2	step;

	if (ray->x > 0)
	{
		step.x = 1;
		dists->x = (float)map_pos.x + 1.0f - pos.x;
	}
	else
	{
		step.x = -1;
		dists->x = pos.x - (float)map_pos.x;
	}
	if (ray->y > 0)
	{
		step.y = 1;
		dists->y = (float)map_pos.y + 1.0f - pos.y;
	}
	else
	{
		step.y = -1;
		dists->y = pos.y - (float)map_pos.y;
	}
	return (step);
}

static float	fast_mag(t_vec2 vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

static int	get_map_type(int64_t x, int64_t y)
{
	t_map_info	*map;

	map = get_map_infos();
	return (map->map[y][x]);
}

static t_vec2	get_grid_pos(t_vec2 pos)
{
	t_vec2	grid_pos;

	grid_pos.x = (int)pos.x - ((int)pos.x % (int)CELL_WIDTH);
	grid_pos.y = (int)pos.y - ((int)pos.y % (int)CELL_HEIGHT);
	return (grid_pos);
}

static void	print_vec(const char *msg, t_vec2 vec)
{
	printf("%s %f %f\n", msg, vec.x, vec.y);
}
