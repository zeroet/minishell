/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:29:27 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 02:11:54 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit = 0;

int			check_whitespace(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != 32 && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

t_cmd			*ft_new(char *line, int pipe, char **envp, int exit)
{
	t_cmd		*result;

	if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	(void)line;
	(void)envp;
	result->cmdline = cmd_split(line, ' ');
	set_token(result->cmdline, envp);
	result->pipe_flag = pipe;
	if (exit == 0 && pipe == 0)
		result->exit_flag = 1;
	else
		result->exit_flag = 0;
	result->err_manage.errcode = 0;
	result->err_manage.errindex = 0;
	result->err_manage.errtoken = NULL;
	result->next = NULL;
	return (result);
}

int				main(int argc, char **argv, char **envp)
{
	char		*line;
	t_cmd		*cmd_list;
	char		**env;
	int i = 0;
//	dup2(STDIN, 100); // fd가 가리키는 기능을 변경하는 함수입니다. 표준입출력에 해당하는 fd를 100, 101에 백업합니다.
//	dup2(STDOUT, 101);
	argc = 1;
	(void)argv;
	env = copy_envp(envp);
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	set_signal();
	while ((line = readline("minishell $ ")))
	{
		if (*line != '\0' && !check_whitespace(line)) // 프롬프트상에서 입력된 문자가 null이거나 모두 white_space일 때는 밑의 로직을 생략합니다.
		{
			add_history(line);
			parse(&cmd_list, line, env); // 입력된 문자열을 먹기좋게 파싱합니다.
	//		g_exit = exec(cmd_list, argv, &env); // 파싱된 명령어 및 문자열을 실행합니다.
	//		free_list(cmd_list); // 파싱된 데이터가 들어있는 list를 해제시켜줍니다.
		}
		free(line); // readline으로 할당한 line을 해제시켜줍니다.
	}
	ft_putstr_fd("\x1b[1A", STDOUT);
 	ft_putstr_fd("\033[12C",STDOUT);
 	ft_putstr_fd("exit\n", STDOUT);
	return (0);
}
