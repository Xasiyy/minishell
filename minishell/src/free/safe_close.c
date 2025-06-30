/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:37:47 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/28 17:39:49 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_close(int *fd)
{
	if (!fd || *fd < 0)
		return (0);
	if (fcntl(*fd, F_GETFD) == -1 && errno == EBADF)
	{
		*fd = -1;
		return (0);
	}
	if (close(*fd) == -1)
		return (-1);
	*fd = -1;
	return (0);
}
