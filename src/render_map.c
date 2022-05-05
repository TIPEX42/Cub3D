/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:11:29 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 15:40:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "error_utils.h"

static void	draw_cells(int cell_size, t_vec2 offset);
static void	render_mmap_wall(int x, int y, int cell_size);
static void	render_mmap_empty(int x, int y, int cell_size);

void	render_mmap(int zoom)
{
	int			cell_size;
	t_vec2		player_pos;
	t_vec2		offset;
	t_mlx		*app;

	app = get_app();
	cell_size = MMAP_ZOOM_FACTOR * zoom;
	player_pos.x = MMAP_W / 2 + MMAP_PAD;
	player_pos.y = MMAP_H / 2 + MMAP_PAD;
	offset.x = -(app->player.pos.x / CELL_WIDTH)
		* cell_size - cell_size / 2 + player_pos.x;
	offset.y = -(app->player.pos.y / CELL_HEIGHT)
		* cell_size - cell_size / 2 + player_pos.y;
	render_rect((t_vec2){MMAP_PAD / 2, MMAP_PAD / 2},
		(t_vec2){MMAP_W + MMAP_PAD, MMAP_H + MMAP_PAD},
		create_trgb(0, 51, 51, 51));
	draw_cells(cell_size, offset);
	render_circle(player_pos, MMAP_PLAYER_DIAM,
		create_trgb(0, 255, 0, 0));
}

static void	draw_cells(int cell_size, t_vec2 offset)
{
	t_map_info	*map;
	size_t		i;
	size_t		j;
	int			x_start;
	int			y_start;

	map = get_map_infos();
	x_start = offset.x;
	y_start = offset.y;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == WALL)
				render_mmap_wall(x_start + j * cell_size,
						y_start + i * cell_size, cell_size);
			if (map->map[i][j] == EMPTY)
				render_mmap_empty(x_start + j * cell_size,
						y_start + i * cell_size, cell_size);
			j++;
		}
		i++;
	}
}

static void	render_mmap_wall(int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			if (!outside_mmap_bounds(x + j, y + i))
				mlx_pixel_put_img(x + j, y + i,
					create_trgb(0, 150, 150, 150));
			j++;
		}
		i++;
	}
}

static void	render_mmap_empty(int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			if (!outside_mmap_bounds(x + j, y + i))
				mlx_pixel_put_img(x + j, y + i,
					create_trgb(0, 250, 250, 250));
			j++;
		}
		i++;
	}
}

int	outside_mmap_bounds(int x, int y)
{
	if (x < MMAP_PAD || x > MMAP_PAD + MMAP_W || y < MMAP_PAD || y > MMAP_PAD
		+ MMAP_H)
		return (1);
	return (0);
}
