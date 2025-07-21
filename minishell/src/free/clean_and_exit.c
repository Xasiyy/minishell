/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:11 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/20 16:09:12 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Affiche un message d'erreur et quitte le shell
void	handle_error(const char *msg)
{
	perror(msg);
	clean_and_exit(get_shell_context(NULL), EXIT_FAILURE);
}
