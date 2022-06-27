/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game_menu_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:48:19 by njennes           #+#    #+#             */
/*   Updated: 2022/06/26 17:46:06 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

int					btn_new_game_back(t_button *button);
int					btn_new_game_down(t_button *button);
int					btn_new_game_up(t_button *button);
int					btn_start_new_game(t_button *button);
int					btn_select_save1(t_checkbox *checkbox);
int					btn_select_save2(t_checkbox *checkbox);
int					btn_select_save3(t_checkbox *checkbox);
int					btn_select_save4(t_checkbox *checkbox);
int					btn_select_save5(t_checkbox *checkbox);
int					btn_unselect_save1(t_checkbox *checkbox);
int					btn_unselect_save2(t_checkbox *checkbox);
int					btn_unselect_save3(t_checkbox *checkbox);
int					btn_unselect_save4(t_checkbox *checkbox);
int					btn_unselect_save5(t_checkbox *checkbox);

void				init_textures(void);
void				init_save_button(t_ui_new_game_menu *menu);
void				update_display_status(void);
inline static void		init_positions_new_game_menu(void);

void	init_new_game_menu(void)
{
	t_ui_new_game_menu	*menu;
	t_settings			*settings;

	settings = get_settings();
	menu = &get_ui()->new_game_menu;
	menu->selected_save = -1;
	menu->btn_back = create_button("assets/ui/left_arrow.xpm",
			ivec2(50, settings->win_h - 50), btn_new_game_back);
	menu->btn_down = create_button("assets/ui/down_arrow.xpm",
			ivec2(0, 0), btn_new_game_down);
	menu->btn_up = create_button("assets/ui/up_arrow.xpm",
			ivec2(0, 0), btn_new_game_up);
	menu->btn_start = create_button("assets/ui/start_button.xpm",
			ivec2(0, 0), btn_start_new_game);
	menu->btn_start.infos.displayed = FALSE;
	init_save_button(menu);
	update_display_status();
	init_textures();
	init_positions_new_game_menu();
}

void	init_save_button(t_ui_new_game_menu *menu)
{
	menu->btn_save[0] = create_checkbox(NULL, ivec2(0, 100),
			btn_select_save1, btn_unselect_save1);
	menu->btn_save[1] = create_checkbox(NULL, ivec2(0, 0),
			btn_select_save2, btn_unselect_save2);
	menu->btn_save[2] = create_checkbox(NULL, ivec2(0, 0),
			btn_select_save3, btn_unselect_save3);
	menu->btn_save[3] = create_checkbox(NULL, ivec2(0, 0),
			btn_select_save4, btn_unselect_save4);
	menu->btn_save[4] = create_checkbox(NULL, ivec2(0, 0),
			btn_select_save5, btn_unselect_save5);
}

inline static void	init_positions_new_game_menu(void)
{
	t_ui_new_game_menu	*menu;

	menu = &get_ui()->new_game_menu;
	uic_padding(&menu->btn_save[0].infos, ivec2(25, 40), ivec2(50, 50));
	uic_padding(&menu->btn_save[1].infos, ivec2(40, 40), ivec2(50, 50));
	uic_padding(&menu->btn_save[2].infos, ivec2(40, 40), ivec2(50, 50));
	uic_padding(&menu->btn_save[3].infos, ivec2(40, 40), ivec2(50, 50));
	uic_padding(&menu->btn_save[4].infos, ivec2(40, 40), ivec2(50, 50));
	uic_padding(&menu->btn_down.infos, ivec2(50, 50), ivec2(50, 50));
	uic_center_win_w(&menu->btn_save[0].infos);
	uic_above(&menu->btn_start.infos, &menu->btn_save[0].infos);
	uic_side_right(&menu->btn_up.infos, &menu->btn_save[0].infos);
	uic_below(&menu->btn_down.infos, &menu->btn_up.infos);
	uic_below(&menu->btn_save[1].infos, &menu->btn_save[0].infos);
	uic_below(&menu->btn_save[2].infos, &menu->btn_save[1].infos);
	uic_below(&menu->btn_save[3].infos, &menu->btn_save[2].infos);
	uic_below(&menu->btn_save[4].infos, &menu->btn_save[3].infos);
}

void	init_textures(void)
{
	t_ui_new_game_menu	*menu;
	t_checkbox			*checkbox;
	int64_t				i;
	t_mlx				*app;

	menu = &get_ui()->new_game_menu;
	i = 0;
	app = get_app();
	while (i < 5)
	{
		checkbox = &menu->btn_save[i];
		if (i < app->maps_count && (checkbox->infos.displayed
				|| checkbox->tex_id == INVALID_TEXTURE))
		{
			checkbox->tex_id = new_texture(250, 50);
			clear_texture(trgb(0, 255, 51, 51), checkbox->tex_id);
			render_text_tex(app->maps[i].name, DEFAULT_FONT,
				text_center(app->maps[i].name, DEFAULT_FONT, 30,
					ivec2(125, 25)),
				ivec2(30, checkbox->tex_id));
			finish_new_texture(checkbox->tex_id);
			checkbox->infos.size = get_texture_size(checkbox->tex_id);
		}
		i++;
	}
}
