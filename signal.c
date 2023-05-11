/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daijeong <daijeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:38:12 by daijeong          #+#    #+#             */
/*   Updated: 2023/05/11 20:59:23 by daijeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	// sigset_t	mask;
	// sigset_t	prev;

	// sigemptyset(&mask);
	// sigaddset(&mask, SIGQUIT);
	// sigprocmask(SIG_BLOCK, &mask, &prev);
	// sigaction(SIGQUIT, &(struct sigaction){SIG_IGN}, 0);
	signal(SIGQUIT, SIG_IGN);
}
