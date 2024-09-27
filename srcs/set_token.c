/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:04:56 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 02:19:39 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int		unclosed_quote(char *str, char quote)
{
	int		idx;

	idx = 1;
	while (str[idx] && str[idx] != quote)
		idx++;
	if (str[idx] == '\0')
		return (0);
	return (1);
}

int		single_quote_size(char *str, int *size)
{
	int		idx;

	idx = 1;
	while(str[idx] && str[idx] != '\'')
	{	
		idx++;
		(*size)++;
	}
	return (idx);
}

int		double_quote_size(char *str, int *size, char **envp)
{
	int		idx;

	idx = 1;
	while (str[idx] && str[idx] != '\"')
	{
		if (str[idx] == '$')
			idx += (env_size(&str[idx], size, envp) + 1);
		else
		{
			idx++;
			(*size)++;
		}
	}
	return (idx);
}

int		get_parse_size(char *str, char **envp)
{
	int		idx;
	int		size;

	size = 0;
	idx = -1;
	while(str[++idx])
	{
		if (str[idx] == '\'' && unclosed_quote(&str[idx], '\'')) 
			idx += single_quote_size(&str[idx], &size);
		else if (str[idx] == '\"' && unclosed_quote(&str[idx], '\"'))
			idx += double_quote_size(&str[idx], &size, envp);
		else if (str[idx] == '$')
			idx += env_size(&str[idx], &size, envp);
		else if (str[idx])
			size++;
	}
	return (size);
}

t_token		*set_token(t_token *token, char **envp)
{
	int		cmd_len;
	size_t	i;
	char	*tmp_cmd;

	i = 0;
	while (token[i].cmd)
	{
		cmd_len = 0;
		tmp_cmd = token[i].cmd;
		cmd_len = get_parse_size(tmp_cmd, envp);
		/*if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
		{
			if (redirec_check(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char*)malloc(sizeof(char) * (cmd_len + 1));
		copy_str(tmp_cmd, token[i].cmd, envp);*/
		free(tmp_cmd);
		i++;	
	}
	return (token);
}
