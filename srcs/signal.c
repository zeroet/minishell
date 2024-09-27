/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:37:29 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/26 19:39:42 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handler(int signum)
{
	if (signum == SIGINT)
		printf("minishell > \n");//CTRL+C 새로운 프롬프터 생성
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	set_signal(void)
{
	struct termios term;//터미널을 제어할수 있는 구조체

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL); //^c출력문제 해결
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handler);// CTRL + C 새로운 프롬프터 생성
	signal(SIGQUIT, SIG_IGN);//CTRL + \ 아무일없다
}
