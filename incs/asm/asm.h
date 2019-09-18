/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:19:41 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/18 02:13:11 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define OK		0
# define NOT_OK	1

# include <unistd.h>
# include <stdlib.h>

# define ERR_FILE			1
# define ERR_EXTENSION		2
# define ERR_NOFILE			3
# define ERR_OVERFLOW		4

# define ERR_STR_FILE		"filename too short"
# define ERR_STR_EXTENSION	"file extension is not correct"
# define ERR_STR_NOFILE		"no given file"
# define ERR_STR_OVERFLOW	"too much argument given"

int			asm_open_file(t_env *e, char *file);
int			asm_file(int ac, char **av);

#endif
