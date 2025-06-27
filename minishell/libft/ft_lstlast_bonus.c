/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:29:46 by asdiallo          #+#    #+#             */
/*   Updated: 2024/10/23 22:07:15 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
/* int main ()
{
	t_list *liste = NULL;

    liste = ft_lstnew("node 1");
    liste->next = ft_lstnew("node 2");
    liste->next->next = ft_lstnew("node 3");

	t_list *lst = ft_lstlast(liste);
    printf("%s\n", (char *)lst->content);

    return 0;
} */