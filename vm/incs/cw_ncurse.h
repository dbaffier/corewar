/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ncurse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:40:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 00:04:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_NCURSE_H
# define CW_NCURSE_H

# include <ncurses.h>
# include "op.h"

typedef struct		s_ncurse
{
	WINDOW			*mainWin;
	WINDOW			*arenaWinBox;
	WINDOW			*arenaWin;
	WINDOW			*infoWinBox;
	WINDOW			*infoWin;
	WINDOW			*infoLine;
}					t_ncurse;

struct s_ncurse		ncu;

#endif
