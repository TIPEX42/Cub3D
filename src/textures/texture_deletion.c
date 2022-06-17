/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_deletion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:57:27 by njennes           #+#    #+#             */
/*   Updated: 2022/06/06 13:04:54 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "leaky.h"
#include "mlx.h"
#include "core.h"

void	free_texture(t_texture *texture)
{
	gc_free(texture->ao_all);
	gc_free(texture->ao_right);
	gc_free(texture->ao_left);
	gc_free(texture->ao_flat);
	gc_free(texture->vflip);
	gc_free(texture->name);
	if (texture->original_handle)
		mlx_destroy_image(get_mlx(), texture->original_handle);
	if (texture->grayscale_handle)
		mlx_destroy_image(get_mlx(), texture->grayscale_handle);
	if (texture->inversed_handle)
		mlx_destroy_image(get_mlx(), texture->inversed_handle);
	if (texture->inversed_grayscale_handle)
		mlx_destroy_image(get_mlx(), texture->inversed_grayscale_handle);
	gc_memset(texture, 0, sizeof(t_texture));
}
