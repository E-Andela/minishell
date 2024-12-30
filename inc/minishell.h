
#ifndef MINISHELL_H
# define MINISHELL_H

// # include "../lib_liath/lib_liath.h"
# include "structs.h"
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

# define RED		"\033[91m"
# define GREEN		"\033[92m"
# define BLUE		"\033[94m"
# define YELLOW		"\033[93m"
# define DEFAULT	"\033[0m"

# define USER_MSG	"user: "

# define ERR_ARGC	"Minishell does not take any arguments.\n"
# define ERR_QUOTES	"Missing closing quote.\n"
# define ERR_TOKEN	"Tokenizer failed.\n"
# define ERR_MALLOC	"Malloc returned NULL.\n"

extern int g_signal;

// debugging.c  -> 	TAKE THIS OUT!!!!
void			print_linked_list(t_env_list *linked_list);
void			print_tokens(t_tokens *token_list);
void			print_cmd_list(t_command *command_list);
// ---------------------------------------------------------------------

// error_handling.c 
// void	error_unexpected_token(t_tokens *type, char *token);
void	error_unexpected_token(t_tokens *token_list);
void	error_not_a_valid_identifier(char** identifier);
int		error_command_not_found(char *cmd);
void	error_ambiguous_redirect(t_tokens *token_list);
void	display_error(char *error_msg);
void	shell_exit(t_error_type error);

// free_and_exit.c 
void			free_command_list(t_command *command_list);
void			free_tokens_list(t_tokens *token_list);
void			free_data(t_data *data);
void			reset_data(t_data *data);
void			exit_program(char *error_message, int errnbr, t_data *data);

// builtin_utils.c
int				is_builtin(t_command *cmd);
int				execute_builtin(char **args, t_env_list *env_list);

// exec.c
void			execute_cmds(t_command *cmd_list, t_env_list *env_list);
int				wait_for_children(t_command *cmd_list);
// int				execute_commands(t_command *cmd_list, t_env_list *env_list);
void execute_cmds(t_command *cmd_list, t_env_list *env_list);
// int	wait_for_children(void);
int execute_commands(t_command *cmd_list, t_env_list *env_list);
int	count_cmds(t_command *cmd_list);
char	*ft_getenv(char *name, char **envp);
char	*get_path(char *command, char *full_path);
int handle_redirections(t_redirections *red_list);
void close_pipes(int **pipes, int size);
void handle_pipes(int **pipes, t_command *cmd_list, int size);
int **create_pipes(int num_pipes);

// new_exec.c
int execute_commands(t_command *cmd_list, t_env_list *env_list);

// ft_cd.c
int	ft_cd(char **args, t_env_list *env_list);

// ft_echo.c
int				ft_echo(char **arg);

// ft_env.c
int				ft_env(char **envp);

//ft_exit.c
int	ft_exit(char **args);

// ft_envp.c
t_env_list		*ft_arr2ll(char **envp);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_ll2arr(t_env_list *envp);
int				ft_max(int a, int b);
t_env_list		*ft_getenvp(char *key, t_env_list *list);
int				get_eq_index(char *element);
t_env_list		*new_element(char *envp);
void			add_element_back(t_env_list **list, t_env_list *new);
void			free_envp(t_env_list *head);
t_env_list		*duplicate_node(t_env_list *node);
void			swap_nodes(t_env_list *a, t_env_list *b);

// ft_export.c
int				ft_export(char **args, t_env_list *env_list);

// ft_pwd.c
int				ft_pwd(char **args, t_env_list *env_list);

// ft_unset.c
int				ft_unset(char **args, t_env_list **env_list);

// here_doc.c
int				handle_here_doc(t_redirections *red_list);
int				create_heredocs(t_command *cmd_list);
int				redirect_heredoc(t_redirections *redirection);


// expander_utils.c
char			*get_environment_key(char	*input, int *i, t_data *data);
char			*get_environment_key_values(t_data *data, char	*input);
bool			ambiguous_redir(t_tokens *current_node, char *token_value, t_data *data);

// expander.c 
bool			expander_check(t_tokens	*token_list, t_data	*data);
bool			expand_token(t_tokens *token_node, char **token_value, t_data *data);
void			remove_quotes(char **token_value, t_data *data);

// vectors.c
void			vector_add_char(t_vector *vector, char c, t_data *data);
void			vector_init(t_vector *vector, t_data *data);

// env_parsing.c 
void			parse_env(char **envp, t_data *data);

// parser_init_nodes.c
t_redirections	*init_redirection_node(char *file, t_token_type type);
t_command		*init_command_node(void);


// parser.c 
int				parser(t_data *data);

// tokenizer_utils.c
int				find_matching_quote(char *input, int start, int *num_quotes, char quote);
t_token_type	check_token(char c);
int				skip_spaces(char *input, int start);

// tokenizer.c 
int				check_for_quotes(char *input);
int				check_whitespace(char c);
void				tokenizer(char *input, t_data *data);

// tokens_create.c
void				add_token(char *input, t_token_type token_type,
					t_tokens **token_list, t_data *data);

// signals.c
void	init_signals();
void	init_child_signals();
void	init_heredoc_signals();
// main.c
void			mini_loop(t_data *data);

#endif
