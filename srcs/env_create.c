/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:48:12 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/24 18:35:47 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		has_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int		ft_env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (has_equal(envp[i]))
		{
			ft_putstr_fd(envp[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	return (1);
}

char	**copy_envp(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}
