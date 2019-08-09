/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:49:01 by aorji             #+#    #+#             */
/*   Updated: 2019/08/08 16:25:13 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

enum hash_mode sha256(t_input *input)
{
    ft_printf("\n----------I AM sha256----------\n");
    ft_listdisp(input->message);
    return 1;    
}