/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 14:45:44 by livliege      #+#    #+#                 */
/*   Updated: 2024/10/10 15:59:04 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "../lib_liath/lib_liath.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/param.h>
# include <limits.h>

#define RED "\033[91m"
#define GREEN "\033[92m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"
#define DEFAULT "\033[0m"

#define USER_MSG "user: "

#define ERR_ARGC "Minishell does not take any arguments.\n"
#define ERR_QUOTES "Missing closing quote.\n"
#define ERR_TOKEN "Tokenizer failed.\n"
#define ERR_MALLOC "Malloc returned NULL.\n"



typedef struct s_env_list
{
	char				*key;
	char				*key_value;
	struct s_env_list	*next;
}					t_env_list;

typedef enum s_token_type
{
	UNSET,
	CMD,
	WORD,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	PIPE,
	OUT_APPEND,
	OUT_REDIRECT,
	IN_REDIRECT,
	HERE_DOC
}	t_token_type;

typedef struct s_tokens
{
	char			*value;
	t_token_type	type;
	unsigned int 	index;
	// bool 			expandable;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_redirection
{
	char					*file; // or in case of an heredoc this will be the delimiter.
	t_token_type			type;
	struct s_redirection	*next;
}	t_redirections;

typedef struct s_command
{
	int						index;
	char					**args;
	t_redirections			*redirections;
	struct s_command		*prev;
	struct s_command		*next;
}	t_command;

typedef struct s_data
{
	char		*user_input;
	t_env_list	*environment;
	t_tokens	*tokens_list;
	unsigned int	pipe_count;
	t_command	*command_list;

}	t_data;


// debugging.c 
void	print_linked_list(t_env_list *linked_list);
void	print_tokens(t_tokens *token_list);
void	print_cmd_list(t_command *command_list);

// env_parsing.c 
void 	parse_env(char **envp, t_data *data);


// error_handling.c 
int	unexpected_token_error(t_data *data, t_tokens *token_list);


// expander.c 
void expander_check(t_tokens *token_list, t_data *data);


// vectors (expander.c)
#define VECTOR_INIT_CAPACITY 16

typedef struct s_vector {
    char *value;
    int capacity;
    int total;
} t_vector;

void vector_add_char(t_vector *vector, char c);
void vector_init(t_vector *vector);


// free_and_exit.c 
void 	free_tokens(t_tokens *token_list);
void	free_everything(t_data *data);
void	exit_program(char *error_message, int errnbr);


// main.c
void	reset_data(t_data *data);
void mini_loop(t_data *data);


// parser.c 
void    parser(t_data *data);


// tokenizer.c 
int		check_for_quotes(char *input);
int		check_whitespace(char c);
int 	tokenizer(char *input, t_data *data);


// tokens_utils.c
int 	add_token(char *input, t_token_type token_type, t_tokens **token_list);

// exec.c
void execute_cmds(t_command *cmd_list, t_env_list *env_list);
int	wait_for_children(void);
int execute_commands(t_command *cmd_list, t_env_list *env_list);
int	count_cmds(t_command *cmd_list);
char	*ft_getenv(char *name, char **envp);
char	*get_path(char *command, char *full_path);
int handle_redirections(t_redirections *red_list);
void close_pipes(int **pipes, int size);
void handle_pipes(int **pipes, t_command *cmd_list, int size);
int **create_pipes(int num_pipes);


// here_doc.c
int handle_here_doc(t_redirections *red_list);

// ft_envp.c
t_env_list	*ft_arr2ll(char **envp);
char		*ft_strjoin(char const *s1, char const *s2);
char 		**ft_ll2arr(t_env_list *envp);
int			ft_max(int a, int b);
t_env_list *ft_getenvp(char *key, t_env_list *list);
int	get_eq_index(char *element);
t_env_list *new_element(char *envp);
void add_element_back(t_env_list **list, t_env_list *new);
void	free_envp(t_env_list *head);
t_env_list *duplicate_node(t_env_list *node);
void	swap_nodes(t_env_list *a, t_env_list *b);

//	builtin_utils.c
int 	is_builtin(char *cmd);
int 	execute_builtin(char **args, t_env_list *env_list);

// ft_echo.c
int		ft_echo(char **arg);

// ft_pwd.c
int		ft_pwd(void);

// ft_export.c
int		ft_export(char **args, t_env_list *env_list);

// ft_unset.c
int	ft_unset(char **args, t_env_list **env_list);

// ft_env.c
int ft_env(char **envp);

#endif
