/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saves_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:57:26 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 16:13:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "core.h"
#include "leaky.h"

static void	add_to_saves(char *save_name);
static void	grow_saves_array(void);

void	load_all_saves(void)
{
	t_mlx			*app;
	DIR				*dir;
	struct dirent	*curr_dir;

	cub_unset_error();
	app = get_app();
	dir = opendir(APPDATA_DIRECTORY);
	if(dir == NULL)
		return ;
	while ((curr_dir = readdir(dir)) != NULL)
	{
		if(curr_dir->d_type == DT_REG && ft_strcmp(curr_dir->d_name, ".") != 0
			&& ft_strcmp(curr_dir->d_name, "..") != 0 && ft_end_with(curr_dir->d_name, ".save"))
			add_to_saves(curr_dir->d_name);
	}
	closedir(dir);
	cub_unset_error();
}

static void	add_to_saves(char *save_name)
{
	t_mlx		*app;
	t_gamestate	save;

	save = load_game(save_name);
	if (cub_consume_error())
		return ;
	printf("adding %s\n", save_name);
	grow_saves_array();
	app = get_app();
	app->savegames[app->savegames_count] = save;
	app->savegames_count++;
}

static void	grow_saves_array(void)
{
	t_mlx		*app;
	t_gamestate	*new;

	app = get_app();
	new = gc_calloc(app->savegames_count + 1, sizeof (t_gamestate));
	ft_memmove(new, app->savegames, app->savegames_count);
	gc_free(app->savegames);
	app->savegames = new;
}
