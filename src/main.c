/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmrok <rmrok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 16:19:27 by rmrok             #+#    #+#             */
/*   Updated: 2026/09/18 16:19:34 by rmrok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (error_msg("usage: ./cub3D <scenefile.cub>"));
	ft_bzero(&scene, sizeof(t_scene));
	if (parse_scene(argv[1], &scene))
		return (free_scene(&scene), 1);
	return (run_game(&scene));
}
