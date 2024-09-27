/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:58:56 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 02:18:04 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		*ft_free(t_token *tokens, int len)
{
	int		i;

	i = 0;
	while (i < len)
		free(tokens[i++].cmd);
	return (NULL);
}

int			condition_word_len(char const *s, const char c, int *len, t_split *info)
{
	if (info->begin == 0)
	{
		if (*s != c)
		{
			info->begin = 1;
			(*len)++;
		}
	}
	else
	{
		if (*s == c && info->quote == 0)
			return (1);
		else if ((*s == '>' || *s == '<') && info->quote == 0)
			return (1);
		else
			(*len)++;
	}
	return (0);
}

int	ft_word_len(char const *s, const char c)
{
	int		len;
	t_split	info;

	len = 0;
	info.begin = 0;
	info.quote = 0;
	while (*s)
	{
		if(*s == '>' || *s == '<')
			len ++;
		put_quote_flag(s, &info.quote);
		if (condition_word_len(s, c, &len, &info) == 1)
			break;
		s++;
	}
	return (len);
}

char	*token_word(int *idx, char const *s, const char c)
{
	int		word_len;
	char	*word;
	int		i;

	word_len = ft_word_len(&s[*idx], c);
	word = (char *)malloc(sizeof(char) + word_len + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = s[*idx + 1];
		i++;
	}
	word[i] =  '\0';
	*idx += word_len;
	return (word);
}

