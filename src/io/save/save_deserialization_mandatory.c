/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_mandatory.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:26:19 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 13:52:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_error.h"
#include "leaky.h"
#include "render.h"
#include "core.h"
#include "io.h"

int			parse_light(t_gamestate *gamestate, t_map_parser *parser, char *line);
void		construct_map(t_map_info *infos) NOPROF;
int			parse_color(t_rgb *color, t_map_parser *parser, char *line) NOPROF;
int			parse_texture(t_map_info *info, t_map_parser *parser, char *line, int direction) NOPROF;
int			add_map_row(t_map_info *infos, t_map_parser *parser, char *line) NOPROF;
t_bool		is_map_legal(t_map_info *infos, t_map_parser *parser) NOPROF;

inline static int	parse_line_mand(t_gamestate *gamestate, t_map_info *infos, t_map_parser *parser, char *line) NOPROF;
inline static void	setup_player(t_gamestate *save) NOPROF;

int	load_mandatory_map(t_gamestate *save_out, int fd, char *line, char *filename)
{
	t_map_info		*infos;
	t_map_parser	parser;

	ft_memset(save_out, 0, sizeof (t_gamestate));
	ft_memset(&parser, 0, sizeof (t_map_parser));
	infos = &save_out->map;
	ft_memsetl(&infos->tx_list, INVALID_TEXTURE, 4);
	parser.filename = filename;
	parser.map_line_offset = -1;
	while (line)
	{
		parser.line = line;
		if (!parse_line_mand(save_out, infos, &parser, line))
			return (map_print_error(&parser));
		gc_free(line);
		line = ft_trimr(gc_get_next_line(fd));
		parser.line_number++;
	}
	if (!is_map_legal(infos, &parser))
		return (map_print_error(&parser));
	construct_map(infos);
	setup_player(save_out);
	if (!is_player_position_legal(save_out))
		return (0);
	return (1);
}

inline static int	parse_line_mand(t_gamestate *gamestate, t_map_info *infos, t_map_parser *parser, char *line)
{
	static int	map_status = MEMPTY;

	if (parser->line_number == 0)
		map_status = MEMPTY;
	if (ft_strlen(ft_strskip_space(line)) == 0)
		return (1);
	if (ft_isdigit(line[0]) || ft_isdigit(*ft_strskip_space(line)))
	{
		if (map_status == MFINISHED)
			return (map_error(line, parser, MERR_MAP_REDEFINITION));
		map_status = MWIP;
		return (add_map_row(infos, parser, line));
	}
	else if (map_status == MWIP && !is_map_legal(infos, parser))
		return (0);
	else if (map_status == MWIP)
		map_status = MFINISHED;
	if (line[0] == 'C' && line[1] == ' ')
		return (parse_color(&infos->ceiling, parser, ft_strskip_space(line + 1)));
	else if (line[0] == 'F' && line[1] == ' ')
		return (parse_color(&infos->floor, parser, ft_strskip_space(line + 1)));
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (parse_texture(infos, parser, ft_strskip_space(line + 2), NORTH));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (parse_texture(infos, parser, ft_strskip_space(line + 2), SOUTH));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (parse_texture(infos, parser, ft_strskip_space(line + 2), EAST));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (parse_texture(infos, parser, ft_strskip_space(line + 2), WEST));
	else if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(gamestate, parser, ft_strskip_space(line + 2)));
	return (map_error(line, parser, MERR_UNRECOGNIZED_LINE));
}

inline static void	setup_player(t_gamestate *save)
{
	if (save->map.spawn_dir == 'N')
		save->player.direction = PI;
	else if (save->map.spawn_dir == 'E')
		save->player.direction = PI / 2.0;
	else if (save->map.spawn_dir == 'S')
		save->player.direction = 0.0;
	else if (save->map.spawn_dir == 'W')
		save->player.direction = PI * 3.0 / 2.0;
	save->player.world_pos = save->map.spawn_pos;
	update_player(&save->player, FALSE);
}
