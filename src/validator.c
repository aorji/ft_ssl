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

// void parser(int ac, char **av)
// {
//     //create t_argv

//     if (ac < 2)
//     {
//         // input->error = 1;
//         ft_printf("%s", "usage: ft_ssl command [command opts] [command args]\n");
//         return ;
//     }
//     int i = 1;
//     t_argument->hash_func = av[i];
//     while(av[i][1] == '-')
//     {
//         append(t_argument->flags, av[i]);
//     }
//     while (i < ac)
//     {
//         append(t_argument->files, av[i]);
//     }
// }

// int ft_getopt()
// {

// }

// t_argument *parser(int ac, char **av)
// {
//     int i = 1;
//     t_argument *arg_value = (t_argument *)malloc(sizeof(t_argument));

//     if (ac < 2)
//     {
//         // ERROR
//     }
//     arg_value->hash_func = av[i++];
//     if (av[i][1] == '-')
//         i += ft_getopt(ac, av);
//     while (i < ac)
//     {
//         append(arg_value->files, av[i]);
//     }
//     return;
// }

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

