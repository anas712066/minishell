/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:36:40 by mmilitar          #+#    #+#             */
/*   Updated: 2025/04/16 21:52:01 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL1_H
# define SIGNAL1_H

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	setup_signal_handlers(void);

#endif
