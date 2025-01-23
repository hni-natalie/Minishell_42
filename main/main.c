/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:03:11 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/01/23 11:27:07 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int main (int argc, char **argv, char **env)
{
	t_shell	shell;
	
	(void) argv;
	if (argc != 1)
	{
		printf("%s%s%s\n", RED, "Usage: ./minishell", RESET);
		exit(EXIT_FAILURE);
	}
	init_shell(&shell, env);
	start_shell(&shell);
	free_arr(shell.env);
	return (EXIT_SUCCESS);
}

void	start_shell(t_shell *shell)
{
	char	*prompt;
	t_node	*ast;

	while (1)
	{
		g_signal = 0;
		prompt = readline("\033[0;33mminishell$\033[0m ");
		if (!prompt)
		{
			printf("%s%s%s\n", RED, "exit 👋 Bye ~", RESET);
			exit(SUCCESS);
		}
		if (*prompt)
			add_history(prompt);
		if (g_signal == SIGINT)
			handle_sigint(shell);
		ast = parse_node(prompt, shell);
		if (ast == NULL)
			continue ;
		// printf("ast: %d\n", ast->type); // debug
		free_ast(ast);
		free(prompt);
	}
}

/*
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);

	used to handle the SIGINT signal
	which is sent when the user presses Ctrl-C
*/
void	init_shell(t_shell *shell, char **env)
{
	char	**copied_env;
	int		i;
	
	i = 0;
	while (env[i])
		i++;
	copied_env = malloc(sizeof(char *) * (i + 1));
	if (!copied_env)
		shell->env = NULL;
	i = -1;
	while (env[++i])
		copied_env[i] = ft_strdup(env[i]);
	copied_env[i] = NULL;
	shell->env = copied_env;
	shell->last_exit_status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
