/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 07:58:35 by rraja-az          #+#    #+#             */
/*   Updated: 2025/02/24 07:59:39 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_valid_env_name(const char *name)
{
	int	i;
	
	if (!name || !name[0] || ((!isalpha(name[0])) && name[0] != '_'))
		return (false);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// using insertion sort
void sort_export_env(char **export_env)
{
    int i;
    int j;
    char *tmp;

    if (!export_env || !export_env[0])
        return;
    i = 1;
    while (export_env[i])
    {
        tmp = export_env[i];
        j = i - 1;
        while (j >= 0 && ft_strcmp(export_env[j], tmp) > 0)
        {
            export_env[j + 1] = export_env[j];
            j--;
        }
        export_env[j + 1] = tmp;
        i++;
    }
}

void print_export_env(t_shell *shell)
{
    int		i;
	char	*equal;

	
    if (!shell->export_env)
        return;
    i = 0;
    while (shell->export_env[i])
    {
		equal = ft_strchr(shell->export_env[i], '=');
        if (equal)
		{
			*equal = '\0';
			printf("declare -x %s=\"%s\"\n", shell->export_env[i], equal + 1);
			*equal = '=';
		}
		else 
			printf("declare -x %s\n", shell->export_env[i]);
		i++;
	}
	//free_array(shell->export_env);
}