// FIX: MAKE FUNCTION IN PARSER TO HANDLE:

// 	FILE AND DIRECTORY ERRORS:
// 	[x] 	cat Makefile | grep pr | head -n 5 | cd test (mybin) 	bash= bash: cd: test: No such file or directory					minishell= test: No such file or directory  			(exitcode = 1 = correct (command not found))
// 	# check status code		
// 	[x] 	cd ~													bash= goes to /home/livliege									minishell= ~: No such file or directory
// 	[/] 	cd no_file												bash= bash: cd: no_file: No such file or directory				minishell= no_file: No such file or directory
// 	[x] 	cd a b c d												basH= bash: cd: too many arguments								minishell= a: No such file or directory
// 	[x]		Documents/github/minishell_2							bash= bash: Documents/github/minishell_2: Is a directory		minishell= Command not found

// 	SYNTAX ERRORS:	syntax error near unexpected token
// 	[x] 	echo bonjour >>> test									bash= bash: syntax error near unexpected token `>'				minishell= creates file called [>] with [bonjour out] in it. also STDOUT problem again.
// 	[X] 	echo bonjour > > out									bash= bash: syntax error near unexpected token `>'				minishell= creates file called [>] with [bonjour out] in it. also STDOUT problem again.								
// 	[x] 	cat < >													bash= bash: syntax error near unexpected token `>'				minishell= >: No such file or directory
// 	[x] 	cat < <													bash= bash: syntax error near unexpected token `<'				minishell= <: No such file or directory
// 	[x] 	cat > >													bash= bash: syntax error near unexpected token `>'				minishell= maakt file aan met naam [>] waar ik vervolgens in kan schrijven
// 	[x] 	echo hudifg d | | hugdfihd								bash= bash: syntax error near unexpected token `|'				minishell= Command not found

// 	AMBIGUOUS REDIRECT
// 	[x] 	echo bonjour > $test 	# with test not defined			bash= bash: $test: ambiguous redirect							minishell= No such file or directory [\n] bonjour
// 	[x] 	echo bonjour > $test w/ t								bash= bash: $test: ambiguous redirect							(also we dont need to handle \w)

// 	WRONG ERROR (Execve failed: Permission denied)
// 	[x] 	file_name_in_current_dir								bash= Makefile: command not found								minishell= Execve failed: Permission denied
// 	[x] 	$bla # with bla not defined								bash= returns prompt to user. 									minishell= Execve failed: Permission denied
// 	[x] 	$LESS$VAR												bash= returns prompt to user. 									minishell= Execve failed: Permission denied

#include "../../inc/minishell.h"

// int				syntax_checker(t_data *data)
// {
// 	t_redirections *redir;

// 	redir = data->command_list->redirections;
// 	if (redir->type == OUT_APPEND)
// 	{
// 		if(redir->file == '>')
// 		error_unexpected_token()
// 	}



// 		return (true);
// 	if (bad)
// 		return (false);
// }
