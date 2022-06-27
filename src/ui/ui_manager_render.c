/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_manager_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:35:02 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 17:37:37 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"
#include "ui.h"

static void	ingame_ui_render(const t_mlx *app);

int	render_ui(void)
{
	t_mlx			*app;

	app = get_app();
	if (app->state != IN_MENU)
	{
		ingame_ui_render(app);
		return (0);
	}
	if (app->ui.state == MAIN_MENU)
	{
		if (app->maps_count > 0)
			render_main_menu_background();
		else
			clear_screen(BKGD_COLOR);
		render_main_menu();
	}
	else if (app->ui.state == NEW_GAME_MENU)
		render_new_game_menu();
	else if (app->ui.state == OPTION_MENU)
		render_settings_menu();
	else if (app->ui.state == LOAD_MENU)
		render_load_menu();
	return (0);
}

static void	ingame_ui_render(const t_mlx *app)
{
	if (app->ui.state == KEYBINDS_MENU)
		;
	else if (app->ui.state == MAP_MENU)
		render_map_menu();
}
