/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:41:54 by aorji             #+#    #+#             */
/*   Updated: 2019/08/01 17:27:15 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void process_string(t_input *input, int j)
{
    char *message = NULL;
    if ((input->av)[input->position][j + 1] == '\0')                        /* example: "-s" "string" */ 
    {
        if (!(input->av)[input->position + 1])
        {
            ft_printf("%s\n", "md5: option requires an argument -- s\nusage: md5 [-pqrtx] [-s string] [files ...]");
            input->error = INVALIDE_FLAG;
            return;
        }
        message = input->av[input->position + 1];
        set_flag(input, (input->av)[input->position][j], 1);
        (input->position)++;
    }
    else                                                                    /* example: "-sstring" */
    {
        message = ft_strsub(input->av[input->position], j + 1, ft_strlen(input->av[input->position]) - j - 1);
        set_flag(input, (input->av)[input->position][j], 1);
    }
    set_message(input, message, message);
    call_hashing_algorithm(input);
}

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
            if(get_flag(input, 'p')) read_message_from_stdin(input);
            return process_string(input, j);
        }
        set_flag(input, (input->av)[input->position][j], 1);
        j++;
    }
}

void process_flags(t_input *input)
{
    while (input->position < input->ac && (input->av)[input->position][0] == '-' && !(input->error))
    {
        add_flag(input);
        input->position++;
    }
    if (input->position < input->ac)
        input->read_from = FILE_STRING;
}
