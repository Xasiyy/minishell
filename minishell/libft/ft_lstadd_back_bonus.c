/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:13:12 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/23 22:45:30 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*liste;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		liste = *lst;
		while (liste -> next)
			liste = liste->next;
		liste -> next = new;
	}
}
/* int main ()
{
	t_list *liste = NULL;

	ft_lstadd_back(&liste, ft_lstnew("Node 1"));
    ft_lstadd_back(&liste, ft_lstnew("Node 2"));
    ft_lstadd_back(&liste, ft_lstnew("Node 3"));
	
	t_list *ptr = liste;
	while (ptr)
	{
		printf("%s -> ", (char *)ptr->content);
		ptr = ptr->next;
	}
	return (0);
} */