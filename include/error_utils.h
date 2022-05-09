/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:53:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/09 16:23:50 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

/* error_utils.c */
void		ft_ferror(int fd);
void		ft_error_msg(char *msg);
void		ft_free_2d(void **ptr, int i);
int			error_code_msg(int code, char *msg);

#endif
