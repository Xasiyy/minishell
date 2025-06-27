/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:57:37 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/23 21:28:54 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}
/* int main() {
    t_list *liste = NULL;

    ft_lstadd_front(&liste, ft_lstnew("Node 1"));
    ft_lstadd_front(&liste, ft_lstnew("Node 2"));
    ft_lstadd_front(&liste, ft_lstnew("Node 3"));

    int count = ft_lstsize(liste);
    printf("%d\n", count);

    return 0;
} */