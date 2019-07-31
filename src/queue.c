/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:54:32 by aorji             #+#    #+#             */
/*   Updated: 2019/07/30 15:35:08 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void realloc_queue_item(t_list **item, size_t size)
{
    (*item)->content = realloc((*item)->content, size);
    (*item)->content_size = size;
}

void    push_back(t_list **queue, char *item)
{
    t_list *new = ft_lstnew(item, ft_strlen(item));
    t_list *tail = *queue;

    if (!(*queue))
    {
        *queue = new;
        return ;
    }
    while( tail->next )
        tail = tail->next;
    tail->next = new;
    return;
}

t_list  *pop_front( t_list **queue )
{
    t_list *head = *queue;
    *queue = (*queue)->next;
    return head;
}