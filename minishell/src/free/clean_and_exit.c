/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:11 by asdiallo          #+#    #+#             */
/*   Updated: 2025/07/30 13:00:10 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(const char *msg)
{
	perror(msg);
	clean_and_exit(get_shell_context(NULL), EXIT_FAILURE);
}
