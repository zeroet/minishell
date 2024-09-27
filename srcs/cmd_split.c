/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:12:08 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 02:15:47 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_quote_flag(char const *s, int *quote)
{
	if (*s == '"' && ((*quote) == 0 || (*quote) == '"'))
	{
		if ((*quote) == '"')
			(*quote) = 0;
		else
			(*quote) = '"';
	}
	else if (*s == '\'' && ((*quote) == 0 || (*quote) == '\''))
	{
		if ((*quote) == '\'')
			(*quote) = 0;
		else
			(*quote) = '\'';
	}
}

void	get_count(int *redirec, int *count, int *begin, int begin_flag)
{
	if (*redirec)
		(*redirec) = 0;
	if (begin_flag == 1)
		(*begin) = 0;
	(*count)++;
}

void	condition_count(t_split *info, char const *s, const char c, int *count)
{
	if (*s == c && info->quote == 0)
		get_count(&info->redirec, count, &info->begin, 1);
	else if ((*s == '>' || *s == '<') && info->quote == 0)
	{
		if (info->redirec == 0 && *(s - 1) != ' ')
			(*count)++;
		info->redirec++;
	}
	else if (*s != c && *s == '\'' && !(*s == '<' || *s == '>') && info->quote == 0
				&& (*(s - 1) == '>' || *(s - 1) == '<'))
		get_count(&info->redirec, count, &info->begin, 0);
	else if (*s == '\'' && info->quote == '\'' && (*(s - 1) == '>' || *(s - 1) == '<'))
		get_count(&info->redirec, count, &info->begin, 0);
	else if (*s == '"' && info->quote == '"' && (*(s - 1) == '>' || *(s - 1) == '<'))
		get_count(&info->redirec, count, &info->begin, 0);
}

int		split_line(char const *s, const char c)
{
	int count;
	t_split	info;
	
	count = 0;
	info.begin = 0;
	info.quote = 0;
	info.redirec = 0;
	
	while (*s)
	{
		put_quote_flag(s, &info.quote);
		if (info.begin == 0)
		{
			if (*s != c)
				info.begin = 1;
			if (*s == '<' || *s == '>')
				info.redirec++;
		}
		else
			condition_count(&info, s, c, &count);
		s++;
	}
	return (info.begin == 0 ? count : count + 1);
}

t_token		*cmd_split(char const *s, char c)
{
	int		i;
	int		idx;
	t_token	*tokens;

	if (s == NULL)
		return (NULL);
	i = 0;
	idx = 0;
	tokens = (t_token*)malloc(sizeof(t_token) * (split_line(s, c) + 1));
	if (tokens == NULL)
		return (NULL);
	while(s[idx])
		if(s[idx] == c)
			idx++;
		else
		{
			tokens[i].cmd = token_word(&idx, s, c);
			tokens[i].redir_flag = 0;
			if (tokens[i].cmd == NULL)
				return (ft_free(tokens, i));
			i++;
		}
	tokens[i].cmd = 0;
	return (tokens);
}
