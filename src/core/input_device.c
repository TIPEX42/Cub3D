/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:37:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/16 22:42:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	cub_update_mouse_pos(int x, int y)
{
	t_mlx	*app;

	app = get_app();
	app->mouse.pos_x = x;
	app->mouse.pos_y = y;
	if (MOUSE_DEBUG)
		dprintf(STDERR_FILENO, "%d -- %d\n", app->mouse.pos_x, app->mouse.pos_y);
}

t_vec2	cub_get_mouse_pos(void)
{
	t_mlx	*app;
	t_vec2	pos;

	app = get_app();
	pos.x = app->mouse.pos_x;
	pos.y = app->mouse.pos_y;
	return (pos);
}
