/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:03:11 by hni-xuan          #+#    #+#             */
/*   Updated: 2025/02/27 12:07:27 by rraja-az         ###   ########.fr       */
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
	free_array(shell.env);
	return (EXIT_SUCCESS);
}

void	start_shell(t_shell *shell)
{
	char	*prompt;
	t_node	*ast;

	while (1)
	{
		g_signal = 0;
		shell->argv_with_qoutes = 0;
		shell->argv_with_expansion = 0;
		prompt = readline("\001\e[0;33m\002minishell$\001\e[0m\002 ");
		if (!prompt) //handles ctrl_d signal
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
		parse_ast(ast, shell);
		// printf("shell->pipe_in_prompt: %d\n", shell->pipe_in_prompt); // debug
		free(prompt);
		free_ast(ast);
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
	shell->env = copy_env(env);
	shell->export_env = copy_env(env);
	shell->last_exit_status = 0;
	// shell->argv_with_qoutes = 0;
	// shell->argv_with_expansion = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	print_error(char *error, char *prompt)
{
	printf("%s%s%s\n", RED, error, RESET);
	free(prompt);
}
