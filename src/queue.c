/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:54:32 by aorji             #+#    #+#             */
/*   Updated: 2019/07/19 16:42:29 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void    push_back(t_list **message_queue, char *message)
{
    t_list *new = ft_lstnew(message, ft_strlen(message));
    if (!*message_queue)
        *message_queue = new;
    else
        ft_lstadd(message_queue, new);
}

t_list  *pop_front( t_list **message_queue )
{
    t_list *tail = NULL;
    t_list *head = *message_queue;

    if (!head)
        return NULL;
    if (!(head->next))
    {
        tail = head;
        head = NULL;
        return tail;
    }
    while(head->next->next)
    {
        head = head->next;
    }
    tail = head->next;
    head->next = NULL;
    return tail;
}