/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:22:10 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/05 10:38:16 by hni-xuan         ###   ########.fr       */
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
	new_arg = ft_strdup("");
	while (arg[i])
	{
		// printf("arg in while loop: %c\n", arg[i]); // debug
		if (!quote && (arg[i] == '\'' || arg[i] == '\"'))
			check_quote(&quote, arg, &i, OPEN_QUOTE);
		else if (quote == arg[i])
			check_quote(&quote, arg, &i, CLOSE_QUOTE);
		else if (arg[i] == '$' && (quote == '\"' || !quote))
			new_arg = update_arg(arg, &i, new_arg, shell);
		else
			new_arg = join_arg(new_arg, arg, &i, quote);
	}
	return (new_arg);
}

char	*join_arg(char *new_arg, char *arg, int *i, int quote)
{
	int		start;
	char	*append_new_arg;
	
	start = *i;
	while (arg[*i])
	{
		if ((!quote && (arg[*i] == '\'' || arg[*i] == '\"' || arg[*i] == '$'))
			|| (quote == '\'' && arg[*i] == quote) ||
			(quote == '\"' && (arg[*i] == '$' || arg[*i] == quote)))
			break ;
		(*i)++;
	}
	append_new_arg = ft_substr(arg, start, *i - start);
	new_arg = ft_strjoin(new_arg, append_new_arg);
	free(append_new_arg);
	return (new_arg);
}

char	*update_arg(char *arg, int *i, char *new_arg, t_shell *shell)
{
	char	*input;
	char	*updated_input;
	int		start;

	(*i)++;
	// printf("arg in update_arg: %s\n", &arg[*i]); // debug
	if (arg[*i] == '?')
		return ((*i)++, ft_itoa(shell->last_exit_status));
	if (ft_isdigit(arg[*i]))
		return ((*i)++, new_arg);
	if (!(ft_isalnum(arg[*i])) && arg[*i] != '_')
		return (ft_strjoin(new_arg, "$"));
	start = *i;
	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
		(*i)++;
	input = ft_substr(arg, start, *i - start);
	updated_input = get_env(shell->env, input);
	free(input);
	if (!updated_input)
		return (new_arg);
	// printf("updated_input: %s\n", updated_input); // debug
	return (ft_strjoin(new_arg, updated_input));
}

char	*get_env(char **env, char *input)
{
	int		i;
	
	i = -1;
	if (!input || !env)
		return (NULL);
	while (env[++i])
		if (ft_strncmp(env[i], input, ft_strlen(input)) == 0)
			return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}
