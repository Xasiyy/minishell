/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:14:20 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/23 20:50:41 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new -> next = *lst;
	*lst = new;
}

/* int main()
{
	t_list *liste = NULL;

	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");

	ft_lstadd_front(&liste, node3);
	ft_lstadd_front(&liste, node2);
	ft_lstadd_front(&liste, node1);
	while (liste)
	{
		printf("%s -> ", (char *)liste->content);
		liste = liste->next;
	}
	printf("NULL\n");
} */