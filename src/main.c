/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/07/18 17:16:02 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

// run:  ./ft_ssl
// norminette -R CheckForbiddenSourceHeader <filename>

int main(int ac, char **av)
{
    t_input *input = create_input(ac, av);
    // validate input
    validate_input(input);
    if (input->error)
        return 0;
    
    // read message
    (ac > 2) ? read_message_from_file(input) : read_message_from_stdin(input);
    if (input->error)
        return 0;

    // run requested hashing algorithm
    int (*hashing_algorithm[])(t_input *) = {md5, sha256};
    (*hashing_algorithm[input->cmd_opts - 1])(input);

    // system ("leaks a.out");

    return 0;
}