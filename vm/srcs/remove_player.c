/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:45:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 01:38:54 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

#include"ft_printf.h"
t_process			*remove_player(t_process *proc, t_process **head)
{
	t_process	*next;

	next = proc->next;
//ft_printf("freeing %d ptr:%p prev:%p next:%p\n", proc->id, proc, proc->prev, proc->next);
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
	// system("afplay ~/Desktop/roblox-death-sound-effect.mp3 2>&-");
	return (next);
}
