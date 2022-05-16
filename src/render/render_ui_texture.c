/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:37:18 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 23:36:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "core.h"

void	render_ui_texture(int64_t tex_id, int x, int y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->original_handle, x, y);
}

void	render_ui_texture_grayscale(int64_t tex_id, int x, int y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->grayscale_handle, x, y);
}

void	render_ui_texture_inverse_grayscale(int64_t tex_id, int x, int y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->inversed_grayscale_handle, x, y);
}

void	render_ui_texture_inversed(int64_t tex_id, int x, int y)
{
	t_mlx				*app;
	t_texture			*texture;

	texture = get_texture_from_id(tex_id);
	if (!texture)
		return ;
	app = get_app();
	mlx_put_image_to_window(app->mlx, app->win,
			texture->inversed_handle, x, y);
}
