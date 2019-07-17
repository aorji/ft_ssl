/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:36:40 by aorji             #+#    #+#             */
/*   Updated: 2019/07/16 15:28:55 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_input *validate_input(int ac, char **av)
{
    t_input *input = (t_input *)malloc(sizeof(t_input));
    input->error = 0;

    if (ac < 2)
    {
        input->error = 1;
        write(0, "usage: ft_ssl command [command opts] [command args]\n", 52);
        return input;
    }
    
    if (!ft_strcmp(av[1], "md5"))
        input->cmd_opts = 0;
    else if (!ft_strcmp(av[1], "sha256"))
        input->cmd_opts = 1;
    else
    {
        input->error = 2;
        write(0, "ft_ssl: Error: '", 16);
        write(0, av[1], ft_strlen(av[1]));
        write(0, "' is an invalid command.\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n", 99);
    }

    return input;
}

