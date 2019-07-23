/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/23 17:59:37 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static int ft_padding_len(size_t message_len)
{
    int sub = message_len % n;
    return ( sub < a ) ? (a - sub) : (a + n - sub);
}

/*
 * step 1
 */
static void append_padding_bits(t_list **message, size_t from, size_t to)
{
    size_t i = from;
    while(from < to)
    {
        ((uint8_t *)((*message)->content))[from] = PADDING[from - i];
        ++from;
    }
}

/*
 * step 2
 */
static void append_lenght(t_list **message, size_t from, size_t len) //CHECK ORDER
{
    for(size_t i = (*message)->content_size - 1; i >= from; --i)
    {
        ((uint8_t *)((*message)->content))[i] = (uint8_t)len;
        len = len >> BIT_NUM;
    }
}

/*
 * step 3
 */


/*
 * entry piont
 */
int         md5(t_input *input)
{
    ft_printf("\n----------I AM md5----------\n");
    ft_printf("\n-------------RUN------------\n\n");

    //hash each file separately
    while (input->message)
    {
        //get message from queue
        t_list *curr_message = pop_front(&(input->message));
        size_t message_len = curr_message->content_size;
        ft_printf("\n%s\n        ", curr_message->content);
        print_bitset(curr_message->content, curr_message->content_size);
        
        //realloc message->content to have enough memmory for step1 and step2 
        size_t message_bit_len = curr_message->content_size * BIT_NUM;
        int padding_bit_len = ft_padding_len(message_bit_len);
        curr_message->content = realloc(curr_message->content, curr_message->content_size + padding_bit_len/BIT_NUM + b/BIT_NUM);
        curr_message->content_size = curr_message->content_size + padding_bit_len/BIT_NUM + b/BIT_NUM;
        
        //step 1
        ft_printf("step 1: ");
        append_padding_bits(&curr_message, message_len, message_len + padding_bit_len/BIT_NUM);
        print_bitset(curr_message->content, curr_message->content_size - b/BIT_NUM);

        // step 2
        ft_printf("step 2: ");
        append_lenght(&curr_message, message_len + padding_bit_len/BIT_NUM, message_len);
        print_bitset(curr_message->content, curr_message->content_size);
    }
    return 1;
}