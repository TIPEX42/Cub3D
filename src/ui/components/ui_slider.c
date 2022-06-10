/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_slider.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:49:53 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 19:42:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

static void	generate_cursor_texture(t_ivec2 size, t_slider *slider);
static void	generate_bar_texture(t_ivec2 size, t_slider *slider);
static void	update_cursor_pos(t_slider *slider);

t_slider	create_slider(t_ivec2 pos, t_ivec2 size, t_vec3 min_max_val)
{
	t_slider	slider;

	ft_memset(&slider, 0, sizeof (t_slider));
	slider.infos.pos = pos;
	slider.infos.size = size;
	slider.infos.displayed = TRUE;
	slider.selected = FALSE;
	slider.min = min_max_val.x;
	slider.max = min_max_val.y;
	slider.value = min_max_val.z;
	slider.tex_id_bar = new_texture((int)size.x, (int)size.y);
	slider.tex_id_cursor = new_texture((int)size.y * 2, (int)size.y * 2);
	generate_cursor_texture(size, &slider);
	generate_bar_texture(size, &slider);
	update_cursor_pos(&slider);
	return (slider);
}

//TODO: try this style: https://lh3.googleusercontent.com/RYCWIG5RchIPW4uv1OoOp6XshQ7TbRmj1vlf46rbV1uXlFj9k8M3eAQpN-Qg8ePE7CqG6OSXUJhED1tfbF8yiv_su1Mvbz2LEl70Tw=w1064-v0
static void	generate_cursor_texture(t_ivec2 size, t_slider *slider)
{
	draw_circle_tex(ivec2(size.y, size.y),
		size.y * 2, trgb(0, 51, 51, 51), slider->tex_id_cursor);
	draw_circle_tex(ivec2(size.y, size.y),
		size.y * 2 - 2, trgb(0, 170, 170, 170), slider->tex_id_cursor);
	finish_new_texture(slider->tex_id_cursor);
}

static void	generate_bar_texture(t_ivec2 size, t_slider *slider)
{
	draw_rect_tex(ivec2(size.y / 2, 0), ivec2(size.x - size.y, size.y),
		trgb(0, 200, 200, 200), slider->tex_id_bar);
	draw_circle_tex(ivec2(size.y / 2, size.y / 2),
		size.y, trgb(0, 200, 200, 200), slider->tex_id_bar);
	draw_circle_tex(ivec2(size.x - size.y / 2, size.y / 2),
		size.y, trgb(0, 200, 200, 200), slider->tex_id_bar);
	finish_new_texture(slider->tex_id_bar);
}

static void	update_cursor_pos(t_slider *slider)
{
	t_ui_component	*infos;
	int64_t			pos;

	infos = &slider->infos;
	pos = (int64_t)(ft_ilerpf(slider->min, slider->max, slider->value) * infos->size.x);
	slider->cursor_pos_x = pos;
}

void	render_ui_slider(t_slider *slider)
{
	t_ui_component	*infos;

	if (!slider->infos.displayed)
		return ;
	infos = &slider->infos;
	render_ui_texture(slider->tex_id_bar, infos->pos.x, infos->pos.y);
	if (!slider->hovered)
	{
		render_ui_texture(slider->tex_id_cursor,
			infos->pos.x + slider->cursor_pos_x - infos->size.y / 2,
			infos->pos.y - infos->size.y / 2);
	}
	else
	{
		render_ui_texture_inverse_grayscale(slider->tex_id_cursor,
			infos->pos.x + slider->cursor_pos_x - infos->size.y / 2,
			infos->pos.y - infos->size.y / 2);
	}
}
