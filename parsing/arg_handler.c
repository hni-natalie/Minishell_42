/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:22:10 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/27 15:21:37 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_exit_status(int *i, char *new_arg, t_shell *shell)
{
	char	*exit_status;
	char	*new_joined_arg;

	(*i)++;
	exit_status = ft_itoa(shell->last_exit_status);
	new_joined_arg = ft_strjoin(new_arg, exit_status);
	free(new_arg);
	free(exit_status);
	return (new_joined_arg);
}

static char	*append_dollar_sign(char *new_arg, char *dollar_sign)
{
	char	*new_joined_arg;

	new_joined_arg = ft_strjoin(new_arg, dollar_sign);
	free(new_arg);
	return (new_joined_arg);
}

char	*update_arg(char *arg, int *i, char *new_arg, t_shell *shell)
{
	char	*input;
	char	*updated_input;
	int		start;
	char	*new_joined_arg;

	(*i)++;
	if (arg[*i] == '?')
		return (append_exit_status(i, new_arg, shell));
	if (ft_isdigit(arg[*i]))
		return ((*i)++, new_arg);
	if (!(ft_isalnum(arg[*i])) && arg[*i] != '_')
		return (append_dollar_sign(new_arg, "$"));
	start = *i;
	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
		(*i)++;
	input = ft_substr(arg, start, *i - start);
	updated_input = get_env(shell, input);
	free(input);
	if (!updated_input)
		return (new_arg);
	new_joined_arg = ft_strjoin(new_arg, updated_input);
	free(new_arg);
	return (new_joined_arg);
}

char	*get_env(t_shell *shell, char *input)
{
	int		i;
	char	**env;

	i = -1;
	env = shell->env;
	shell->argv_with_expansion = 1;
	if (!input || !env)
		return (NULL);
	while (env[++i])
		if (ft_strncmp(env[i], input, ft_strlen(input)) == 0
			&& env[i][ft_strlen(input)] == '=')
			return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}