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

static void add_flag(t_input *input)
{
    int j = 1;
    while ((input->av)[input->position][j])
    {
        if ((input->av)[input->position][j] < input->flag->flags_opt[0] || (input->av)[input->position][j] > input->flag->flags_opt[no_arg_flag_num - 1])
        {
            ft_printf("%s%c%s\n", "md5: illegal option -- ", (input->av)[input->position][j], "\nusage: md5 [-pqr] [-s string] [files ...]");
            input->error = INVALIDE_FLAG;
            return;
        }
        if ((input->av)[input->position][j] == 's')
        {
            input->read_from = FILE_STRING;
            if ((input->av)[input->position][j + 1] == '\0')            /* example: "-s" "string" */ 
            {
                if (!(input->av)[input->position + 1])
                {
                    ft_printf("%s\n", "md5: option requires an argument -- s\nusage: md5 [-pqrtx] [-s string] [files ...]");
                    input->error = INVALIDE_FLAG;
                    return;
                }
                push_back(&input->message, input->av[input->position + 1]);
                push_back(&input->message_name, input->av[input->position + 1]);
                (input->flag->flags_set)[(input->av)[input->position][j] % (input->flag->flags_opt)[0]] = 1;
                input->position++;
                return;
            }
            else                                                        /* example: "-sstring" */
            {
                push_back(&input->message, ft_strsub(input->av[input->position], j + 1, ft_strlen(input->av[input->position]) - j - 1));
                push_back(&input->message_name, ft_strsub(input->av[input->position], j + 1, ft_strlen(input->av[input->position]) - j - 1));
                (input->flag->flags_set)[(input->av)[input->position][j] % (input->flag->flags_opt)[0]] = 1;
                return;
            }
        }
        (input->flag->flags_set)[(input->av)[input->position][j] % (input->flag->flags_opt)[0]] = 1;
        j++;
    }
}

static void flags_options(t_input *input)
{
    input->position = 2;
    while (input->position < input->ac && (input->av)[input->position][0] == '-' && !(input->error))
    {
        add_flag(input);
        input->position++;
    }
}

static void cmd_options(t_input *input)
{
    if (input->error)
        return;
    if (!ft_strcmp((input->av)[1], "md5"))
        input->cmd_opts = 1;
    else if (!ft_strcmp((input->av)[1], "sha256"))
        input->cmd_opts = 2;
    else
    {
        input->error = INVALIDE_CMD;
        ft_printf("%s%s%s", "ft_ssl: Error: '", (input->av)[1], "' is an invalid command.\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
    }
}

static void param_num(t_input *input)
{
    if (input->ac < 2)
    {
        input->error = NO_CMD;
        ft_printf("%s", "usage: ft_ssl command [command opts] [command args]\n");
    }
}

void validate_input(t_input *input)
{
    param_num(input);
    cmd_options(input);
    flags_options(input);

    if (input->position < input->ac)
        input->read_from = FILE_STRING;
}