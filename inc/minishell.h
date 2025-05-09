/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:16:18 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/22 10:56:10 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/inc/libft.h"
# include <sys/wait.h>
# include <termios.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>

# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_REDIR_APPEND 4
# define TOKEN_REDIR_IN 5
# define TOKEN_REDIR_HEREDOC 6

extern int			g_exit_status;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	int				pipe_in;
	int				pipe_out;
	int				interrupted;
	char			*heredoc_file;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*input;
	char			**env;
	t_env			*env_list;
	char			*path;
	t_cmd			*cmd_list;
	t_token			*tokens;
	int				exit_status;
	int				tmp;
	int				**pipes;
}	t_data;

typedef struct s_child
{
	t_data			*data;
	t_cmd			*current;
	pid_t			*pids;
	int				i;
	int				cmd_count;
	int				pipe_count;
}	t_child;

// ==================== Pars ==================== //
// --------------- Lexer.c --------------- //
t_token				*lexer(char *input);
char				*concatenate_parts(char *part1, char *part2);
char				*process_quoted_part(char *value, size_t *i,
						size_t len, char *processed);
char				*process_unquoted_part(char *value,
						size_t *i, size_t len, char *processed);
char				*process_value(char *value);
t_token				*create_new_token(char *value, int type);
void				append_token(t_token **tokens, t_token *new);
void				add_token(t_token **tokens, char *value, int type);
int					handle_quotes(char *input, int i, char quote);
char				*concatenate_parts(char *part1, char *part2);
int					handle_escaped_characters(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_whitespace(char **current_part, t_token **tokens);
int					handle_quotes_in_lexer(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_redirection_append(int *i, t_token **tokens);
int					handle_redirection_heredoc(int *i, t_token **tokens);
int					handle_redirection_out(int *i, t_token **tokens);
int					handle_redirection_in(int *i, t_token **tokens);
int					handle_redirections(char *input, int *i, t_token **tokens);
int					handle_pipe(char *input, int *i, t_token **tokens);
int					handle_special_characters(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_unquoted_part(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_escape_case(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_whitespace_case(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_quote_case(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_special_char_case(char *input, int *i,
						char **current_part, t_token **tokens);
int					handle_default_case(char *input, int *i,
						char **current_part, t_token **tokens);
int					process_input_char(char *input, int *i,
						char **current_part, t_token **tokens);
int					finalize_tokens(char **current_part, t_token **tokens);

// --------------- Parser.c --------------- //
t_cmd				*parser(t_token *tokens, t_data *data);
// --------------- Expander.c --------------- //
char				*expander(char *input, t_data *data);
char				*handle_empty_dollar(char *result);
char				*handle_single_quotes(char *input, int *i, char *result);
char				*process_dollar_in_quotes(char *input, int *i,
						t_data *data, char *result);
char				*handle_double_quotes(char *input, int *i,
						t_data *data, char *result);
char				*handle_dollar_sign(char *input, int *i,
						t_data *data, char *result);
char				*handle_plain_text(char *input, int *i, char *result);
char				*expand_dollar_variable(char *input, int *i,
						t_data *data, char *result);
char				*expand_variable(char *input, t_env *env_list, int *len);
char				*append_char_to_result(char *result, char *tmp);
char				*process_double_quotes_content(char *input, int *i,
						t_data *data, char *result);
char				*process_single_quotes_content(char *input,
						int *i, char *result);
char				*handle_exit_status_expansion(int *i,
						t_data *data, char *result);
char				*handle_dollar(int *i, char *result);
char				*handle_single_char(char *input, int *i, char *result);
int					check_after_pipe(char *input);

// --------------- Pars.c --------------- //
t_cmd				*parse_input(char *input, t_data *data);
int					handle_redirection_token(t_cmd *current_cmd,
						t_token **tokens, t_cmd *cmd_list);
int					handle_heredoc_token(t_cmd *current_cmd, t_token **tokens,
						t_cmd *cmd_list, t_data *data);
t_cmd				*initialize_command(t_cmd **current_cmd, t_cmd *cmd_list);
int					process_token(t_cmd **current_cmd, t_cmd **cmd_list,
						t_token **tokens, t_data *data);
int					finalize_command(t_cmd *current_cmd, t_cmd *cmd_list);
void				add_redirection(t_redir **redirections, int type,
						char *file);
int					handle_word_token(t_cmd *cmd, t_token *token,
						t_cmd *cmd_list);
int					handle_pipe_token(t_cmd **current_cmd, t_cmd *cmd_list);
int					handle_redirection_file(t_cmd *current_cmd,
						t_token **tokens, t_cmd *cmd_list);
// --------------- Read.c --------------- //
char				*read_input(t_data *data);
void				save_history(char *input);
void				load_history(void);
// -------------- Signal.c --------------- //
void				signal_handler_main(int signum);
void				ft_exec_sig_handler(int sig);
void				setup_signals(t_data *data);
void				handle_parent_signals(void);
void				handle_child_signals(void);
void				setup_exec_signals(void);
void				ft_quit(int sig);
// ==================== Exec ==================== //
// ------------------ builtins --------------- //
// ---------- cd.c ------------ //
int					ft_cd(char **av, t_env *env);
// ---------- echo.c ------------ //
int					ft_echo(int ac, char **av);
// ---------- exit.c ------------ //
void				exit_clean(t_data *data, t_token *tokens, int i);
void				ft_exit(char **args, t_data *data);
// ---------- export.c ------------ //
int					ft_export(char **args, t_env **env);
// ---------- export_utils.c ------------ //
int					is_valid_identifier(char *str);
int					compare_env_vars(t_env *a, t_env *b);
t_env				*copy_env_list(t_env *env);
void				free_env_copy(t_env *env_copy);
// ---------- export_sort.c ------------ //
void				sort_env_list(t_env **head);
void				handle_export_no_value(t_env **env, char *name);
int					print_sorted_env(t_env *env);
int					create_env_node(t_env **env_list, char *env_var);
// ---------- pwd.c ------------ //
int					ft_pwd(void);
// ---------- unset.c ------------ //
int					ft_unset(char **args, t_env **env, t_data *data);
// ------------------ pipes ------------------ //
// ---------- child_processes.c ------------ //
int					exec_cmd_in_child(t_cmd *cmd, t_data *data, char *cmdpath);
int					execute_builtin_with_redirections(t_cmd *cmd, t_data *data);
void				setup_child_pipes(t_data *data, int i, int cmd_count);
int					handle_fork_error(pid_t *pids, int i,
						t_data *data, int pipe_count);
void				handle_command_not_found(t_cmd *current,
						t_data *data, int pipe_count);
// ---------- heredoc.c ------------ //
int					handle_heredoc(char *delimiter, char **heredoc_file,
						t_data *data, t_cmd *cmd_list);
int					handle_heredoc_in_fork(int f[3], char *delimiter,
						t_data *data, char **heredoc_file);
int					write_to_tmp_file(int fd, char *line);
int					handle_delimiter_error(char *delimiter);
int					generate_tmp_file(char *tmp_file, int *file_counter);
int					process_heredoc_in_child(int f[3], char *delimiter);
// ---------- pipe_creation.c ------------ /
int					create_pipes(t_data *data, int pipe_count);
pid_t				*allocate_pids(int cmd_count, int pipe_count, t_data *data);
void				restore_std_fds(int std_fds[2]);
void				cleanup_execution(t_data *data,
						pid_t *pids, int pipe_count);
// ---------- pipe_processes.c ------------ //
int					exec_pipe(t_data *data, int cmd_count, int pipe_count);
int					wait_children(pid_t *pids, int cmd_count, int *exit_status);
// ---------- pipes.c ------------ //
int					count_commands(t_cmd *cmd_list);
void				close_all_pipes(t_data *data, int pipe_count);
void				free_pipes(t_data *data, int pipe_count);
int					execute_piped_commands(t_data *data);

// -------------- execution.c ---------------- //
int					is_builtin(char *cmd);
int					ft_tablen(char **tab);
int					execute_builtin(t_cmd *cmd, t_data *data);
int					execute_external(t_cmd *cmd, t_data *data);
int					execute_single_command(t_cmd *cmd, t_data *data);
int					execute_commands(t_data *data);
int					validate_command(t_cmd *cmd, t_data *data, char **cmd_path);
int					wait_for_child(pid_t pid);
// -------------- redirections.c -------------- //
int					setup_redirections(t_redir *redirections,
						t_data *data, t_cmd *cmd);
int					handle_output_redirection(char *filename, int append);
int					handle_input_redirection(char *filename);

// ==================== Utils ==================== //
// --------------- Utils.c --------------- //
char				*ft_strjoin_free(char *s1, char *s2);
char				**ft_tabjoin(char **tab, char *new_elem);
int					is_directory(const char *path);
int					ft_isspace(char *s);
int					create_tmp_file(char *tmp_file,
						char **heredoc_file, int *fd);
void				delete_temp_files(void);
// ---------- free_cmd.c ------------ //
void				free_cmd_list(t_cmd *cmd_list);
t_cmd				*create_new_command(void);
void				free_pids(pid_t *pids);
void				free_token(t_token *tokens);
void				free_data_members(t_data *data);
void				free_redirections(t_redir *redirections);
void				cleanup_on_interrupt(t_data *data, int pipe_count);
void				signnn(void);
// ---------- get_value.c ------------ //
char				*get_value(t_env env, char *name);
void				update_value(t_env *env, char *name, char *value);
int					add_value(t_env **env, char *name, char *value);
// ---------- init_data.c ------------ //
char				**copy_env(char **env);
char				*get_path(char **env);
t_env				*env_to_list(char **env);
char				*find_command_path(char *cmd, t_data *data);
t_data				*init_data(int ac, char **av, char **env);
int					handle_malloc_error(char *tmp, int fd);
// ---------- print_tab.c ------------ //
void				print_tab(char **tab);
void				print_invalid_identifier_error(char *name);
void				print_list(t_env *env);

#endif
