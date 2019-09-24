/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:45:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/24 03:50:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

t_process			*remove_player(t_process *proc, t_process **head)
{
	t_process	*next;

	next = proc->next;
	if (proc->prev)
		proc->prev->next = proc->next;
	else
		*head = proc->next;
	if (proc->next)
		proc->next->prev = proc->prev;
	free(proc);
	system("afplay ~/Desktop/roblox-death-sound-effect.mp3");
	return (next);
}
