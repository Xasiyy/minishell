/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asdiallo <asiya040906@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:11 by asdiallo          #+#    #+#             */
/*   Updated: 2025/06/22 20:04:31 by asdiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Affiche un message d'erreur et quitte le shell
void	handle_error(const char *msg)
{
	perror(msg);
	clean_and_exit(get_shell_context(NULL), EXIT_FAILURE);
}