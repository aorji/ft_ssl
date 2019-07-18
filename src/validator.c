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

void validate_input(t_input *input)
{
    if (input->ac < 2)
    {
        input->error = 1;
        ft_printf("%s", "usage: ft_ssl command [command opts] [command args]\n");
        return ;
    }
    
    if (!ft_strcmp((input->av)[1], "md5"))
        input->cmd_opts = 1;
    else if (!ft_strcmp((input->av)[1], "sha256"))
        input->cmd_opts = 2;
    else
    {
        input->error = 2;
        ft_printf("%s%s%s", "ft_ssl: Error: '", (input->av)[1], "' is an invalid command.\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
    }
}

