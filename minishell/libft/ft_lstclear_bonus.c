/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:29:43 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/24 12:03:22 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*liste;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		liste = (*lst)-> next;
		del((*lst)-> content);
		free (*lst);
		*lst = liste;
	}
	*lst = NULL;
}
