/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:13:12 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/02 21:31:24 by xasiy            ###   ########.fr       */
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
