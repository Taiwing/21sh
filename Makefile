############################## COMPILE VAR #####################################

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address,undefined
HDIR		=	includes
SRCDIR		=	src
SUB1D		=	libft
HFLAGS		=	-I $(HDIR) -I $(SUB1D)/$(HDIR)
LIBS		=	$(SUB1D)/libft.a
NAME		=	21sh

############################## SOURCES #########################################

BUILTINSDIR		=	builtins
EXECUTIONDIR	=	execution
GLOBALDIR		=	global
INPUTDIR		=	input
LEXINGDIR		=	lexing
PARSINGDIR		=	parsing

SRCC			=	debug.c\
					main.c\
					sh_init.c\

BUILTINSC		=	g_builtins.c\
					shb_alias.c\
					shb_cd.c\
					shb_echo.c\
					shb_env.c\
					shb_exit.c\
					shb_ppt.c\
					shb_ptok.c\
					shb_pwd.c\
					shb_setenv.c\
					shb_unalias.c\
					shb_unsetenv.c\

EXECUTIONC		=	exec_command.c\
					sh_execution.c\

GLOBALC			=	env.c\
					history.c\
					quotes.c\
					sh_signals.c\
					t_shvar_list.c\
					t_shvar_utils.c\
					terminal_size.c\

INPUTC			=	char_functions_1.c\
					char_functions_2.c\
					char_functions_3.c\
					charfunc.c\
					charfunc_utils.c\
					completion_utils.c\
					dllst_insert.c\
					dllst_move.c\
					dllst_remove.c\
					dllst_str.c\
					env_completion.c\
					exec_completion.c\
					file_completion.c\
					input_history.c\
					sh_input.c\
					tab_completion.c\
					terminal_cursor.c\

LEXINGC			=	sh_lexing.c\
					token.c\
					token_utils.c\

PARSINGC		=	build_command.c\
					build_exec_tree.c\
					destroy_exec_tree.c\
					expand.c\
					find_command.c\
					p_functions_1.c\
					p_functions_2.c\
					p_functions_3.c\
					p_functions_4.c\
					p_functions_5.c\
					param_exp.c\
					sh_parsing.c\
					tilde_exp.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(BUILTINSC))\
					$(patsubst %.c,%.o,$(EXECUTIONC))\
					$(patsubst %.c,%.o,$(GLOBALC))\
					$(patsubst %.c,%.o,$(INPUTC))\
					$(patsubst %.c,%.o,$(LEXINGC))\
					$(patsubst %.c,%.o,$(PARSINGC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)/$(BUILTINSDIR)
vpath			%.c	$(SRCDIR)/$(EXECUTIONDIR)
vpath			%.c	$(SRCDIR)/$(GLOBALDIR)
vpath			%.c	$(SRCDIR)/$(INPUTDIR)
vpath			%.c	$(SRCDIR)/$(LEXINGDIR)
vpath			%.c	$(SRCDIR)/$(PARSINGDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS) -ltermcap

$(SUB1D)/libft.a:
	make -C $(SUB1D)

g_builtins.o: g_builtins.h sh_data.h libft.h
shb_alias.o: t_shvar.h libft.h sh_data.h quotes.h
shb_cd.o: sh_data.h libft.h t_shvar.h
shb_echo.o: sh_data.h libft.h
shb_env.o: t_shvar.h libft.h sh_execution.h sh_parsing.h sh_data.h token.h
shb_exit.o: sh_data.h libft.h t_shvar.h
shb_ppt.o: sh_input.h sh_data.h libft.h t_dllst.h sh_lexing.h sh_parsing.h\
	token.h c_colors.h debug.h
shb_ptok.o: sh_lexing.h sh_data.h libft.h debug.h sh_parsing.h token.h
shb_pwd.o: sh_data.h libft.h t_shvar.h
shb_setenv.o: t_shvar.h libft.h sh_data.h
shb_unalias.o: t_shvar.h libft.h sh_data.h
shb_unsetenv.o: t_shvar.h libft.h sh_data.h
debug.o: sh_parsing.h sh_data.h libft.h token.h
exec_command.o: t_shvar.h libft.h g_builtins.h sh_data.h sh_parsing.h token.h\
	sh_signals.h
sh_execution.o: sh_execution.h sh_parsing.h sh_data.h libft.h token.h
env.o: t_shvar.h libft.h
history.o: sh_data.h libft.h
quotes.o: quotes.h libft.h
sh_signals.o: libft.h terminal_size.h terminal_cursor.h sh_data.h
t_shvar_list.o: t_shvar.h libft.h
t_shvar_utils.o: t_shvar.h libft.h
char_functions_1.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h quotes.h\
	tab_completion.h
char_functions_2.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h\
	input_history.h
char_functions_3.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h
charfunc.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h
charfunc_utils.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h quotes.h
completion_utils.o: libft.h
dllst_insert.o: t_dllst.h libft.h
dllst_move.o: t_dllst.h libft.h
dllst_remove.o: t_dllst.h libft.h
dllst_str.o: t_dllst.h libft.h
env_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h\
	t_shvar.h
exec_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h\
	g_builtins.h
file_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h
input_history.o: sh_input.h sh_data.h libft.h t_dllst.h charfunc.h\
	terminal_cursor.h
sh_input.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h quotes.h\
	t_shvar.h c_colors.h terminal_size.h terminal_cursor.h
tab_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h\
	charfunc.h quotes.h terminal_cursor.h
terminal_cursor.o: libft.h sh_input.h sh_data.h t_dllst.h
sh_lexing.o: token.h sh_data.h libft.h quotes.h t_shvar.h sh_lexing.h
token.o: token.h sh_data.h libft.h quotes.h t_shvar.h
token_utils.o: token.h sh_data.h libft.h
main.o: sh_input.h sh_data.h libft.h t_dllst.h sh_lexing.h sh_parsing.h\
	token.h sh_execution.h
build_command.o: sh_parsing.h sh_data.h libft.h token.h
build_exec_tree.o: sh_parsing.h sh_data.h libft.h token.h
destroy_exec_tree.o: sh_parsing.h sh_data.h libft.h token.h
expand.o: tilde_exp.h sh_data.h libft.h param_exp.h quotes.h
find_command.o: sh_parsing.h sh_data.h libft.h token.h g_builtins.h
p_functions_1.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_2.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_3.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_4.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_5.o: sh_parsing.h sh_data.h libft.h token.h
param_exp.o: sh_data.h libft.h quotes.h t_shvar.h
sh_parsing.o: sh_parsing.h sh_data.h libft.h token.h debug.h
tilde_exp.o: sh_data.h libft.h t_shvar.h
sh_init.o: sh_data.h libft.h t_shvar.h sh_signals.h terminal_size.h
%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c $(CFLAGS) $< $(HFLAGS) -o $(ODIR)/$@

$(ODIR):
	mkdir -p $@

############################## CLEANUP #########################################

clean:
	rm -rf $(ODIR)
	make -C $(SUB1D) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
