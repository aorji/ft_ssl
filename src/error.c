/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
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
        ft_printf("%s\n", "usage: ft_ssl command [command opts] [command args]");
        return input;
    }
    
    if (!ft_strcmp(av[1], "md5"))
        input->cmd_opts = 0;
    else if (!ft_strcmp(av[1], "sha256"))
        input->cmd_opts = 1;
    else
    {
        input->error = 2;
        ft_printf("%s%s%s", "ft_ssl: Error:'", av[1], "' is an invalid command.\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
    }

    return input;
}

