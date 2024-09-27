/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 01:50:49 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/02 02:20:49 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env_value_size(char *str, int size, char **envp)
{
	int		idx;

	idx = -1;
	while (envp[++idx])
	{
		if ((!ft_strncmp(&str[1], envp[idx], size)) && envp[idx][size] == '=')
			return (ft_strlen(envp[idx] + size + 1));
	}
	return (0);
}

int		env_key_size(char *str)
{
	int		idx;

	idx = 0;
	if (ft_isdigit(str[1]))
		return (1);
	while (str[++idx])
	{
		if (!(ft_isalnum(str[idx]) || str[idx] == '_'))
			return (idx - 1);
	}
	return (idx - 1);
}

int		env_size(char *str, int *size, char **envp)
{
	int		idx;
	char	*exit_status;

	idx = 0;
	if (str[1] == '?')
	{
		exit_status = ft_itoa(g_exit);
		*size += ft_strlen(exit_status);
		free(exit_status);
		return (1);
	}
	if (str[1] == '\0' || str[1] == '\"')
	{
		*size += 1;
		return (0);
	}
	idx = env_key_size(str);
	*size += env_value_size(str, idx, envp);
	return (idx);
}
