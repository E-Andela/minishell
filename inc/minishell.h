/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: livliege <livliege@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 16:03:44 by livliege      #+#    #+#                 */
/*   Updated: 2025/01/16 16:03:44 by livliege      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <sys/stat.h>

# define RED		"\033[91m"
# define GREEN		"\033[92m"
# define BLUE		"\033[94m"
# define YELLOW		"\033[93m"
# define DEFAULT	"\033[0m"

# define USER_MSG	"user: "

# define ERR_ARGC	"Minishell does not take any arguments.\n"
# define ERR_QUOTES	"unexpected EOF while looking for matching quote.\n"
# define ERR_TOKEN	"Tokenizer failed.\n"
# define ERR_MALLOC	"Malloc failed.\n"
# define ERR_INPUT	"Readline function returned NULL.\n"

extern int	g_signal;

// debugging.c  -> 	TAKE THIS OUT!!!!
void			print_linked_list(t_env_list *linked_list);
void			print_tokens(t_tokens *token_list);
void			print_cmd_list(t_command *command_list);
// ---------------------------------------------------------------------

// error_handling.c 
void			error_unexpected_token(t_data *data, t_tokens *token_list);
void			error_not_a_valid_identifier(char *identifier);
int				error_command_not_found(char *cmd);
void			error_ambiguous_redirect(t_data *data, t_tokens *token_list);
void			display_error(char *error_msg);

// free_and_exit.c 
void			free_data(t_data *data);
void			reset_data(t_data *data);
void			exit_program(char *error_message, int error, t_data *data);
void			shell_exit(t_error_type error);

// free_lists.c
void			free_command_list(t_command *command_list);
void			free_tokens_list(t_tokens *token_list);
void			free_env_list(t_env_list *env_list);

// builtin_utils.c
int				is_builtin(t_command *cmd);
int				execute_builtin(char **args, t_env_list **env_list);

// exec.c
int				wait_for_children(t_command *cmd_list);
void			check_if_directory(char *path, t_command *cmd_list);
// int			execute_commands(t_command *cmd_list, t_env_list *env_list);
// int			wait_for_children(void);
int				execute_commands(t_command *cmd_list, t_env_list **env_list);
int				count_cmds(t_command *cmd_list);
char			*ft_getenv(char *name, char **envp);
char			*get_path(char *command, char *full_path);
int				handle_redirections(t_redirections *red_list);
void			close_pipes(int **pipes, int size);
void			handle_pipes(int **pipes, t_command *cmd_list, int size);
int				**create_pipes(int num_pipes);

// ft_cd.c
int				ft_cd(char **args, t_env_list *env_list);

// ft_echo.c
int				ft_echo(char **arg);

// ft_env.c
int				ft_env(char **envp);

//ft_exit.c
int				ft_exit(char **args);

// ft_envp.c
t_env_list		*ft_arr2ll(char **envp);
int				ll_count(t_env_list *list, bool skip_null);
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
char			*get_envp_value(char *key, t_env_list *env_list);

// export_utils.c
int				valid_var_name(char	*name);
char			*get_key(char *key_value);
char			*get_value(char *key_value);
void			sort_envp_list(t_env_list *head);
t_env_list		*dup_envp_list(t_env_list *head);

// export_utils2.c
int				arg_counter(char **args);

// ft_export.c
int				ft_export(char **args, t_env_list *env_list);

// ft_pwd.c
int				ft_pwd(t_env_list *env_list);

// ft_unset.c
int				ft_unset(char **args, t_env_list **env_list);

// here_doc.c
int				handle_here_doc(t_redirections *red_list);
int				create_heredocs(t_command *cmd_list);
int				redirect_heredoc(t_redirections *redirection);

// expander_utils.c
char			*get_environment_key(char	*input, int *i);
char			*get_environment_key_values(t_data *data, char	*input);
bool			is_redirect(t_token_type type);
bool			ambiguous_redir(t_data *data, t_tokens *current_node);

// expander.c 
bool			expander_check(t_tokens	*token_list, t_data	*data);
bool			expand_token(t_tokens *token_node,
					char **token_value, t_data *data);
void			remove_quotes(char **token_value, t_data *data);
t_vector		*expand_exit_code(t_vector *vector, t_data *data);

// hande_environment.c
void			expand_env_variable(t_vector *vector, int *i,
					char *token_value, t_data *data);
// handle_quotes.c
void			expand_double_quotes(t_vector *vector, int *i,
					char *token_value, t_data *data);
void			expand_single_quotes(t_vector *vector, int *i,
					char *token_value, t_data *data);

// vectors.c
void			vector_add_char(t_vector *vector, char c, t_data *data);
void			vector_init(t_vector *vector, t_data *data);

// env_parsing.c 
void			parse_env(char **envp, t_data *data);

// parser_init_nodes.c
t_redirections	*init_redirection_node(char *file, t_token_type type);
t_command		*init_command_node(void);
void			init_cmd_nodes(t_command **new_cmd_node, \
					t_command **head_cmd_node, t_command **current_cmd_node, \
					t_data *data);

// parser_utils.c
void			add_redirection(t_command *cmd, char *file, \
					t_token_type type, t_data *data);
void			add_argument(t_command *cmd, char *arg);
void			set_index(t_command *cmd_list);
bool			check_if_redirect(t_token_type type);

// parser.c 
int				parser(t_data *data);

// tokenizer_utils.c
int				find_matching_quote(char *input, int start,
					int *num_quotes, char quote);
t_token_type	check_token(char c);
int				skip_spaces(char *input, int start);

// tokenizer.c 
bool			check_for_quotes(char *input);
int				check_whitespace(char c);
void			tokenizer(char *input, t_data *data);

// tokens_create.c
void			add_token(char *input, t_token_type token_type,
					t_tokens **token_list, t_data *data);

// signals.c
void			init_signals(void);
void			init_child_signals(void);
void			init_heredoc_signals(void);

// signal_handlers.c
void			sigint_handler(int signal);
void			sigint_handler_child(int signal);
void			sigint_handler_heredoc(int signal);
void			quit(int signal);

// main.c
void			mini_loop(t_data *data);
void			execute_and_handle_exit(t_data *data);
bool			process_input(t_data *data);

// shell_lvl.c
void			increase_shlvl(t_env_list *env_list);

// tester.c
int				run_tester(t_data *data);

#endif
