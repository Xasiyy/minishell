/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xasiy <xasiy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:00:52 by ncullu            #+#    #+#             */
/*   Updated: 2025/07/03 13:02:28 by xasiy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include "get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_INPUT 1024

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	QUOTE_NONE,
	QUOTE_SIMPLE,
	QUOTE_DOUBLE
}								t_quote_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}								t_redir_type;

typedef struct s_redir
{
	t_redir_type				type;
	char						*filename;
	struct s_redir				*next;
}								t_redir;

typedef struct s_segment
{
	char						*value;
	t_quote_type				quote;
	struct s_segment			*next;
}								t_segment;

typedef struct s_files
{
	char						*file1;
	char						*file2;
}								t_files;

typedef struct s_command
{
	char						**args;
	char						*infile;
	char						*outfile;
	int							append;
	int							heredoc;
	char						*delimiter;
	int							has_pipe;
	int							has_redirection;
	char						*path;
	t_redir						*redirections;
	struct s_command			*next;
}								t_command;

typedef struct s_pipeline
{
	t_command					*commands;
	int							count;
}								t_pipeline;

typedef struct s_env
{
	char						**envp;
}								t_env;

typedef struct s_shell
{
	int							last_exit_status;
	t_pipeline					*pipeline;
	t_env						*env;
	pid_t						main_pid;
}								t_shell;

typedef struct s_pipe_state
{
	int							i;
	int							part_i;
	int							start;
}								t_pipe_state;

// builtins.c
// builtins_cd.c
int								builtin_cd(char **cmd);
int								execute_cd(char *target, t_shell *shell);

// builtin_core.c.c
int								is_builtin(char **cmd);
int								execute_builtin(char **cmd, int *exit_status);
int								execute_builtin_redirection(t_command *cmd,
									int *exit_status);
int								is_valid_n_option(char *arg);
t_command						*build_cmd_list(t_command **cmds);

// builtins_echo.c
int								builtin_echo(char **cmd);

// builtins_env.c
int								builtin_pwd(void);
int								builtin_env(char **env);
int								builtin_unset(char **cmd, t_env *env_struct);
int								env_var_exists(char **env, const char *key);

// builtins_exit_parent_child.c
int								is_too_many_args(char **cmd, t_shell *shell);
void							check_numeric_exit(char *arg, t_shell *shell,
									long long *exit_code);
void							handle_exit_parent(char **cmd, t_shell *shell);
void							handle_exit_child(char **cmd, t_shell *shell);

// builtins_exit.c
int								is_valid_numeric(const char *str);
long long						ft_strtoll(const char *str, int *error);
void							builtin_exit(char **cmd, t_shell *shell);

// builtins_export.c
int								builtin_export(char **cmd, t_env *env_struct);
int								export_process_args(char **cmd,
									t_env *env_struct);
int								handle_export_with_value(t_env *env_struct,
									char *arg, char *equal);
int								is_valid_identifier(const char *str);

// builtins_utils.c
int								is_safe_in_parent(t_command *cmd);
int								is_safe_in_executed_parent(char *name);
// heredoc.c
char	*handle_heredoc(char *delimiter);

// command_path
// command_path.c
char							*find_command_in_path(char *cmd, char **env);
char							*check_access(char *cmd);
char							*find_command_in_env_path(char *cmd,
									char **env);
char							*try_path(char *cmd_path, char *cmd);
char							*handle_direct_path(char *cmd);

// context_env
// context_env.c
t_shell							*get_shell_context(t_shell *set_shell);
t_shell							*get_shell_from_env(t_env *env);
t_env							*init_env(char **envp);

// env
// env_display.c
void							sort_env(char **env);
void							print_sorted_env(char **env);

// env_unset.c.c
int								unset_env_var(char ***env, const char *key);

// env_utils.c
char							**copy_env(char **envp);
int								add_env_entry(char ***env, const char *key,
									const char *value);
int								set_env_var(char ***env, const char *key,
									const char *value);
int								copy_old_env(char **new_env, char **old_env,
									int count);

// execution
// chid_utils.c
void							fork_and_run_child(t_command *cmd, char **env,
									int prev_fd, int pipe_fd[2]);
void							create_pipe(int *pipe_fd);
pid_t							create_process(void);

// execution_child.c
char							*resolve_command_path(t_command *cmd,
									char **env);
void							execute_child(t_command *cmd, char **env);

// execution.c
void							execute_command(t_command *cmd, char **env,
									int *exit_status);
void							execute_external_builtin(char **args,
									char **env, int *exit_status);
void							execute_external(t_command *cmd, char **env,
									int *exit_status);
void							handle_parent_process(pid_t pid, int *status,
									int *exit_status);
void							execute_commands(t_command *cmd_list,
									t_env *env);

// execve_handler.c
void							handle_execve_errors(t_command *cmd,
									int via_path_search);

// handle_redirection.c
int								handle_redirections(t_command *cmd);
// pipeline.c
void							execute_pipeline(t_pipeline *pipeline,
									char **env);
int								execute_child_process(t_command *cmd,
									char **env, int prev_fd, pid_t *pid_out);
int								setup_pipe(int pipe_fd[2], t_command *cmd);
int								handle_parent_after_fork(pid_t pid,
									t_command *cmd, int prev_fd,
									int pipe_fd[2]);
void							wait_for_all_children(t_shell *shell,
									pid_t last_pid);
// redirection.c
int								get_fd_from_redir(t_redir *redir);

// free
//safe_close.c 
int								safe_close(int *fd);
// clean_exit.c
void							exit_with_perror(char *filename);
void							handle_error(const char *msg);

// free_shell.c
void							free_shell(t_shell *shell, int force_env);
void							clean_and_exit(t_shell *shell, int exit_code);
char							*ft_join_free_left(char *s1, const char *s2);
char							*ft_join_free_both(char *s1, char *s2);

// free_utils.c
void							free_all(t_shell *shell);
void							free_command_list(t_command *cmd_list);
void							free_command(t_command *cmd);
void							free_env(t_env *env);
void							free_segments(t_segment *seg);

// memory_utils.c
void							free_split(char **split);
char							*ft_strjoin_free(char *s1, char *s2);

// helpers
// env_helpers.c
char							*get_env_value(char **env, const char *var);
char							*find_path_in_env(char **env);
void							ft_error(char *msg);

// execution_helpers.c
void							setup_child_pipes(int fd_in, int *pipe_fd);
void							child_process(t_command *cmd, char **env,
									int *exit_status);
void							setup_parent_pipes(int fd_out, int *pipe_fd);
void							parent_process(t_command *cmd, char **env,
									int *exit_status);

// line_handler
// line_handler.c
void							handle_line(char *line, t_shell *shell);
int								handle_quotes_and_history(char *line,
									t_shell *shell);
void							execute_pipeline_or_single(t_shell *shell);

// main
// main.c
void							start_shell_loop(t_shell *shell);

// parsing
// expander.c
char							*expand_variables(char *str, int quote_type,
									t_shell *shell);

// parsing_check.c
int								syntax_error(char **tokens);
void							remove_empty_args(t_command *cmd);

// parsin_entry.c
t_command						*parsing(char *input, t_shell *shell);
t_command						*build_command(char **tokens, int *quote_flags,
									t_shell *shell);
int								*init_quote_flags(char **tokens);
char							**parsing_token_setup(char *input);
void							expand_all_tokens(char **tokens,
									t_shell *shell);
char							*lexer_treatline(char *s);	

// parsing_field_splitting.c
void							discard_empty_words(char **tok, int *quote);

// parsing_pipeline.c
t_pipeline						*parse_pipeline(char *input, t_shell *shell);
t_pipeline						*allocate_pipeline(char **parts,
									t_command **cmds);

// parsing_redirec.c
int								is_quoted(const char *s);
void							parse_redirections(char **tok, int *flags,
									t_command *cmd);

// parsing_redirection.c
void							add_redirection(t_command *cmd,
									t_redir_type type, char *filename);
void							expand_all_tokens_with_quotes(char **tokens,
									int *quote_flags, t_shell *shell);
void	handle_redirection(char **tokens, int *i, t_command *cmd);
t_redir_type					get_redirection_type(char *t);
char							*extract_redirection_filename(char **tokens,
									int *i);

// parsing_syntax.c
int								is_pipe(char *tok);
void							print_unexpected(char *tok);
int								expect_filename(char **t, int *i);
int								check_tokens(char **t);

// parsing_tok.c
char							*parse_and_expand_token(const char *token,
									t_shell *shell);
char							*build_expanded_string(t_segment *segments,
									t_shell *shell);

// parsing_tokens.c
size_t							count_redir_pieces(char *t);
void							fill_token(const char *str, char **tokens,
									int *i, int *tok_i);
char							**split_tokens(const char *str);

// parsing_trim.c
char							*trim_withespaces(const char *str);
int								has_unclosed_quotes(const char *str);

// parsing_utils.c
int								is_space(char c);
int								count_tokens(const char *str);
int								is_special(char *token);
int								is_redirection(char *token);

// parsing.c
char							*get_var_name(const char *str, int *i);
char							*append_char_to_result(char *result, char c);
char							*expand_and_append_var(char *str, int *i,
									t_shell *shell);
char							*append_expanded_to_result(char *result,
									char *expanded);

// segmentation_quotes.c
t_segment						*new_segment(char *value, t_quote_type quote);
void							append_segment(t_segment **list,
									t_segment *new_seg);
void							handle_segment_quote(const char *input, int *i,
									t_segment **segments);
t_segment						*split_segments(const char *input);

// Plit_internat_redirs.c
void							split_token_redirs(char *t, char **out,
									size_t *j);
char							**split_internat_redirs(char **tokens);

// split_pipeline.c
int								count_pipeline_parts(const char *str);
void							update_quote(char c, char *quote);
int								handle_pipe_split(const char *str, char **parts,
									t_pipe_state *st);
char							**split_pipeline_tokens(const char *str);

// split_quotes.c
char							**ft_realloc_split(char **old, int new_size);
char							*extract_token(const char *input, int *i);
char							**split_respecting_quotes(const char *input);

// shell_main
// shell_main.c
void							exec_cmds(t_files files, int pipe_fd[2],
									t_command *cmd, char **env);
void							minishell(t_files files, char *input,
									char **env);

// signal
// signals.c
void							setup_interactive_signals(void);
void							sigint_handler(int signo);
void							sigqquit_handler(int signo);
void							init_signals(void);
void							handle_sigint(int sig);
void							heredoc_sigint(int signo);

// utils
// file_utils.c
int								open_input_file(const char *file);
int								open_output_file(const char *file);
void							cleanup_and_exit(int fd, int *pipe_fd);

// ft_strdup_array.c
char							**ft_strdup_array(char **src);

#endif
