
/*
	1. store_env(t_shell *shell)
	2. get_key(char *key)
	3. get_path(char *key)
	4. is_key(char *key, t_shell *shell)
	5. update_env (char *key, char *path, bool add, t_shell *shell)
	6. extend_env_array 
*/

/*
	ENV (with no options or no arguments)
	DESC: Prints all environment variables in newline

	FLOW:
		1. init env (done in init_shell)
			- store_env populate shell->env with env from envp
			- extract key and value via get_key and get_val
			- then calls update_env to add to the array
		2. manage env var
			- check, add, update, store env dynamically
		3. handle env cmd
			- iterates env list and prints those only with values
			- return exit status
	
	FUNCTIONS:
		1. store_env (t_shell *shell) > done in main->init shell
		2. get_key (char *key) > WHY? easier to just compare via name
			- extract name  > ft_strchr(env_var, '=') to find the =.
							> ft_substr(env_var, 0, index_of('=')) to extract the name
		3. get_path (char *key) > WHY? 
			- directly extracts path without going through KEY=PATH
			- used in store to populate (but we dont need this)
			- handle edge case without value
			- used when need to expand variable ($VAR) 
				- EG : run echo $SHELL
					 : /bin/bash

		4. is_key (char *key, t_shell *shell) 
			- (key exist) > WHY? check if var exist before modifying or adding it
			**prevent duplicate
			- EG: ["PATH=/usr/bin", "HOME=/home/user", "SHELL=/bin/bash", NULL]
				- run > export PATH=/new/path > REPLACE existing PATH
			**determine whether to add / update (export)
			- EG : if name exist > update its value | if name x exist > add new variable
				- export EDITOR=vim > if EDITOR exist, value gets updated to vim, else add EDITOR=vim to array
			**used with update env
			- EG : if true > update existing value, else add new "KEY=VALUE"
			** ensure proper unset behaviour
			- when removing env > check if exist before removing
			- if not found, unset does nothing

		5. update_key (char *key, char *path, bool add, t_shell *shell)
			- if key exist > update the path; find in array and replace it
				- free old path, replace with new path
			- if name doesnt exist > add new entry
				- reallocate shell->env[] to hold new var
				- append "KEY=PATH" to the array > set len to NULL
*/




