/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:22:10 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/27 12:40:17 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_arg(char **argv, t_shell *shell)
{
	char	*new_arg;
	int		i;

	i = -1;
	while (argv[++i])
	{
		// printf("argv[%d]: %s\n", i, argv[i]); // debug
		new_arg = check_arg(argv[i], shell);
		free(argv[i]);
		argv[i] = new_arg;
		// printf("after argv[%d]: %s\n", i, argv[i]); // debug
	}
}

/*
	reason why we need to use join_arg
		as we go through the entire arg character by character
		we need to join the characters together to form a new_arg 
		then only return the new_arg
*/
char	*check_arg(char *arg, t_shell *shell)
{
	char	*new_arg;
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	if (ft_strcmp(arg, "\0") == 0)
		return (arg);
	new_arg = ft_strdup("");
	while (arg[i] && i < (int)ft_strlen(arg))
	{
		// printf("arg in while loop: %c\n", arg[i]); // debug
		if (!quote && (arg[i] == '\'' || arg[i] == '\"'))
			check_quote(&quote, arg, &i, OPEN_QUOTE);
		else if (quote == arg[i])
		{
			check_quote(&quote, arg, &i, CLOSE_QUOTE);
			shell->argv_with_qoutes = 1;
		}
		else if (arg[i] == '$' && (quote == '\"' || !quote))
			new_arg = update_arg(arg, &i, new_arg, shell);
		else
			new_arg = join_arg(new_arg, arg, &i, quote);
		// printf("arg = %s\n", new_arg); //debug
	}
	return (new_arg);
}

char	*join_arg(char *new_arg, char *arg, int *i, int quote)
{
	int		start;
	char	*append_new_arg;
	char	*new_joined_arg;
	
	start = *i;
	new_joined_arg = NULL;
	while (arg[*i])
	{
		if ((!quote && (arg[*i] == '\'' || arg[*i] == '\"' || arg[*i] == '$')) ||
			(quote == '\'' && arg[*i] == quote) ||
			(quote == '\"' && (arg[*i] == quote || arg[*i] == '$')))
				break ;
		(*i)++;
	}
	append_new_arg = ft_substr(arg, start, *i - start);
	new_joined_arg = ft_strjoin(new_arg, append_new_arg);
	free(new_arg);
	free(append_new_arg);
	return (new_joined_arg);
}

static char	*append_exit_status(int *i, char *new_arg, t_shell *shell)
{
	char	*exit_status;
	char	*new_joined_arg;

	(*i)++;
	exit_status = ft_itoa(shell->last_exit_status);
	// printf("exit_status = %s\n", exit_status);
	new_joined_arg = ft_strjoin(new_arg, exit_status);
	// printf("new_joined_arg = %s\n", new_joined_arg);
	free(new_arg);
	free(exit_status);
	return (new_joined_arg);
}

static char *append_dollar_sign(char *new_arg, char *dollar_sign)
{
	char	*new_joined_arg;
	
	// printf("check\n");
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
	// printf("arg in update_arg: %s\n", &arg[*i]); // debug
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
	// printf("updated_input: %s\n", updated_input); // debug
	// printf("new_arg: %s\n", new_arg); // debug
	new_joined_arg = ft_strjoin(new_arg, updated_input);
	// printf("new_joined_arg: %s\n", new_joined_arg); // debug
	// if (ft_strcmp(new_arg, "") != 0)
	free(new_arg);
	// free(updated_input);
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
