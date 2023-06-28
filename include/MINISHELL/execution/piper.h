/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:42:09 by htsang            #+#    #+#             */
/*   Updated: 2023/06/28 21:13:02 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPER_H
# define PIPER_H

# include <stdbool.h>

/////////////////////////////////////////////
////////////   piper interface   ////////////
/////////////////////////////////////////////

struct s_ms_piper
{
	int		pipe1[2];
	int		pipe2[2];
	bool	pipe1_opened : 1;
	bool	pipe2_opened : 1;
	bool	sender_is_pipe1 : 1;
};

void	ms_piper_init(struct s_ms_piper *piper);

int		ms_piper_destroy(struct s_ms_piper *piper);

int		ms_piper_create_sender(struct s_ms_piper *piper);

void	ms_piper_create_receiver(struct s_ms_piper *piper);

int		ms_piper_use_sender(struct s_ms_piper *piper);

int		ms_piper_close_receiver(struct s_ms_piper *piper);

int		ms_piper_use_receiver(struct s_ms_piper *piper);

/**
 * @brief private interface
*/

int		*ms_piper_get_sender_pipe(struct s_ms_piper *piper);

int		*ms_piper_get_receiver_pipe(struct s_ms_piper *piper);

bool	ms_piper_pipe_is_open(struct s_ms_piper *piper, int *pipe);

int		ms_piper_set_pipe_status(struct s_ms_piper *piper, int *pipe, \
bool piped);

int		ms_piper_close_pipe(int *pipe);

#endif