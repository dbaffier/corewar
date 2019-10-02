/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:45:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/02 18:50:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

t_process			*remove_player(t_process *proc, t_process **head)
{
	t_process	*next;

	next = proc->next;
	if (proc->prev)
		proc->prev->next = proc->next;
	else
		*head = next;
	if (proc->next)
		proc->next->prev = proc->prev;
	if (proc->file)
		free(proc->file);
	ft_bzero(proc, sizeof(*proc));
	free(proc);
	return (next);
}

/*
** system("afplay ~/Desktop/roblox-death-sound-effect.mp3 2>&-");
*/
