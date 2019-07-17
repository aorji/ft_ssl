/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/07/17 19:35:03 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

//run:  ./ft_ssl

void pprint()
{
    write(1, "testp\n", 6);
}
int main(int ac, char **av) {

    t_input *input = create_input();
    // validate input
    validate_input(input, ac, av);
    if (input->error)
        return 0;
    
    // read message
    (ac > 2) ? read_message_from_file(input, ac, av) : read_message_from_stdin(input);
    if (input->error)
        return 0;

    // run requested hashing algorithm
    int (*hashing_algorithm[])(t_input *) = {md5, sha256};
    (*hashing_algorithm[input->cmd_opts - 1])(input);

    // system ("leaks a.out");

    return 0;
}