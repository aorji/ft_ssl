/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:54:32 by aorji             #+#    #+#             */
/*   Updated: 2019/07/22 20:20:32 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void    push_back(t_list **message_queue, char *message)
{
    t_list *new = ft_lstnew(message, ft_strlen(message));
    t_list *tail = *message_queue;

    if (!(*message_queue))
    {
        *message_queue = new;
        return ;
    }
    while( tail->next )
        tail = tail->next;
    tail->next = new;
    return;
}

t_list  *pop_front( t_list **message_queue )
{
    t_list *head = *message_queue;
    *message_queue = (*message_queue)->next;
    return head;
}