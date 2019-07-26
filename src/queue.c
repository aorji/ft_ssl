/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:54:32 by aorji             #+#    #+#             */
/*   Updated: 2019/07/26 13:19:22 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void realloc_queue_item(t_list **item, size_t len)
{
    (*item)->content = realloc((*item)->content, len);
    (*item)->content_size = len;
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