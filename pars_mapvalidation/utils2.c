/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouras <mbouras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:40:02 by mbouras           #+#    #+#             */
/*   Updated: 2025/03/10 21:08:05 by mbouras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_ac(int ac)
{
	if (ac != 2)
	{
		write(2,"invalide arg",12);
		exit(1);
	}
}
void	err_msg(void)
{
	write(2, "Error\nU CANT PLAY\n", 19);
	exit(1);
}
void	err_msg2(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

