/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:23:53 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 15:14:13 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "profiling.h"

# define BLACK		0x00000000
# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF
# define WHITE		0x00FFFFFF
# define PINK		0x00FF00FF
# define YELLOW		0x00FFFF00
# define TURQUOISE	0x0000FFFF

# define BKGD_COLOR		0x0037464B

# define CEILLING		0x000099CC
# define FLOOR			0x00666666
# define WALL_COLOR_1	0x00e65c00
# define WALL_COLOR_2	0x00b34700

/* colors */
int			trgb(int t, int r, int g, int b)
NOPROF;
int			get_t(int trgb)
NOPROF;
int			get_r(int trgb)
NOPROF;
int			get_g(int trgb)
NOPROF;
int			get_b(int trgb)
NOPROF;

/* colors utils */
int			color_lerp(int col1, int col2, double value);

#endif
