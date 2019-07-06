/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/07/06 20:20:48 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ssl.h"

int main(int ac, char **av) {

    // validate input
    t_input *input = validate_input(ac, av);
    if (input->error)
        return 0;
    
    // read message
    (ac > 2) ? read_message_from_file(input, av[2]) : read_message_from_stdin(input);
    if (input->error)
        return 0;

    ft_printf("%s", input->message);
    // system ("leaks a.out");
    
    //run md5
    if (!ft_strcmp(input->message, "md5"))
        return run_md5(input);
    
    // run sha256
    else if (!ft_strcmp(input->message, "sha256"))
        return run_sha256(input);

    return 0;
}