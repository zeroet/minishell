/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:54:42 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 00:19:24 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_flag(int *i, int *start, int *pipe, int *quote)
{
	(*i) = 0;
	(*start) = 0;
	(*quote) = 0;
	(*pipe) = 1;
}

void	check_quote(char *line, int quote, int i)//따옴표 닫혀있는지 확인 
{
	if ((line[i] == '\"' || line[i] == '\'') && quote == 0)
		quote = 1;
	else if ((line[i] == '\"' || line[i] == '\'') && quote == 1)
		quote = 0;
}

void	check_pipe(char *line, int pipe, int i)
{
		if (line[i] == '|')
			line[i] = '\0';//파이프를 널로 대체 나중에 스플릿위해
		else
			pipe = 0;
}

void	add_new(t_cmd **cmd_list, t_cmd **new, t_cmd **tmp, int start)
{
	if (start == 0)
	{
		*cmd_list = *new;
		*tmp = *cmd_list;
	}
	else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
	{
		(*cmd_list)->next = *new;
		*cmd_list = (*cmd_list)->next;
	}
}

void			parse(t_cmd **cmd_list, char *line, char **envp)
{
	int			i;
	int			start;
	int			pipe;
	t_cmd		*tmp;
	t_cmd		*new;
	int			quote;

	init_flag(&i, &start, &pipe, &quote);
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		check_quote(line, quote, i);
		if (line[i] == '\0' || (line[i] == '|' && quote == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			check_pipe(line, pipe, i);
			if ((new = ft_new(&line[start], pipe, envp, start)) == 0)
				return ;
			add_new(cmd_list, &new, &tmp, start);
			if (pipe == 0) // 마지막 노드이므로 while loop를 벗어납니다.
				break ;
			start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	*cmd_list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
