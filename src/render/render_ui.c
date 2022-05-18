/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:42:46 by njennes           #+#    #+#             */
/*   Updated: 2022/05/18 14:59:32 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "render.h"

void	render_ui_label(t_label *label)
{
	render_ui_texture(label->tex_id, label->infos.pos.x, label->infos.pos.y);
}
