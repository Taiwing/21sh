############################## COMPILE VAR #####################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra
#CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address,undefined
HDIR		=	includes
SRCDIR		=	src
SUB1D		=	libft
HFLAGS		=	-I $(HDIR) -I $(SUB1D)/$(HDIR)
LIBS		=	$(SUB1D)/libft.a
NAME		=	21sh

############################## SOURCES #########################################

GLOBALDIR		=	global
PARSINGDIR		=	parsing
INPUTDIR		=	input
LEXINGDIR		=	lexing
EXECUTIONDIR	=	execution
BUILTINSDIR		=	builtins

SRCC			=	sh_init.c\
					debug.c\
					main.c\

GLOBALC			=	quotes.c\
					history.c\
					terminal_size.c\
					sh_signals.c\
					t_shvar_list.c\
					t_shvar_utils.c\
					env.c\

PARSINGC		=	build_exec_tree.c\
					find_command.c\
					sh_parsing.c\
					param_exp.c\
					p_functions_5.c\
					p_functions_3.c\
					tilde_exp.c\
					p_functions_4.c\
					p_functions_2.c\
					build_command.c\
					destroy_exec_tree.c\
					p_functions_1.c\
					expand.c\

INPUTC			=	dllst_str.c\
					completion_utils.c\
					file_completion.c\
					tab_completion.c\
					dllst_insert.c\
					dllst_move.c\
					input_history.c\
					char_functions_3.c\
					terminal_cursor.c\
					env_completion.c\
					sh_input.c\
					charfunc_utils.c\
					char_functions_2.c\
					exec_completion.c\
					dllst_remove.c\
					char_functions_1.c\
					charfunc.c\

LEXINGC			=	token_utils.c\
					token.c\
					sh_lexing.c\

EXECUTIONC		=	exec_command.c\
					sh_execution.c\

BUILTINSC		=	shb_ppt.c\
					shb_exit.c\
					shb_env.c\
					shb_cd.c\
					shb_unsetenv.c\
					shb_unalias.c\
					shb_alias.c\
					shb_ptok.c\
					g_builtins.c\
					shb_setenv.c\
					shb_echo.c\
					shb_pwd.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(GLOBALC))\
					$(patsubst %.c,%.o,$(PARSINGC))\
					$(patsubst %.c,%.o,$(INPUTC))\
					$(patsubst %.c,%.o,$(LEXINGC))\
					$(patsubst %.c,%.o,$(EXECUTIONC))\
					$(patsubst %.c,%.o,$(BUILTINSC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)/$(GLOBALDIR)
vpath			%.c	$(SRCDIR)/$(PARSINGDIR)
vpath			%.c	$(SRCDIR)/$(INPUTDIR)
vpath			%.c	$(SRCDIR)/$(LEXINGDIR)
vpath			%.c	$(SRCDIR)/$(EXECUTIONDIR)
vpath			%.c	$(SRCDIR)/$(BUILTINSDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS) -lncurses

$(SUB1D)/libft.a:
	make -C $(SUB1D)

sh_init.o: sh_data.h libft.h t_shvar.h sh_signals.h terminal_size.h
quotes.o: quotes.h libft.h
history.o: sh_data.h libft.h
sh_signals.o: libft.h terminal_size.h terminal_cursor.h
t_shvar_list.o: t_shvar.h libft.h
t_shvar_utils.o: t_shvar.h libft.h
env.o: t_shvar.h libft.h
build_exec_tree.o: sh_parsing.h sh_data.h libft.h token.h
find_command.o: sh_parsing.h sh_data.h libft.h token.h g_builtins.h
sh_parsing.o: sh_parsing.h sh_data.h libft.h token.h debug.h sh_parsing.h
param_exp.o: sh_data.h libft.h quotes.h t_shvar.h
p_functions_5.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_3.o: sh_parsing.h sh_data.h libft.h token.h
tilde_exp.o: sh_data.h libft.h t_shvar.h
p_functions_4.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_2.o: sh_parsing.h sh_data.h libft.h token.h
build_command.o: sh_parsing.h sh_data.h libft.h token.h
destroy_exec_tree.o: sh_parsing.h sh_data.h libft.h token.h
p_functions_1.o: sh_parsing.h sh_data.h libft.h token.h
expand.o: tilde_exp.h sh_data.h libft.h param_exp.h quotes.h
dllst_str.o: t_dllst.h libft.h
completion_utils.o: libft.h
file_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h
tab_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h\
	charfunc.h quotes.h terminal_cursor.h
dllst_insert.o: t_dllst.h libft.h
dllst_move.o: t_dllst.h libft.h
input_history.o: sh_input.h sh_data.h libft.h t_dllst.h charfunc.h sh_input.h\
	terminal_cursor.h
char_functions_3.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h
terminal_cursor.o: libft.h sh_input.h sh_data.h t_dllst.h
env_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h\
	t_shvar.h
sh_input.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h quotes.h\
	t_shvar.h c_colors.h terminal_size.h terminal_cursor.h
charfunc_utils.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h quotes.h
char_functions_2.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h\
	input_history.h
exec_completion.o: tab_completion.h sh_input.h sh_data.h libft.h t_dllst.h\
	g_builtins.h
dllst_remove.o: t_dllst.h libft.h
char_functions_1.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h quotes.h\
	tab_completion.h
charfunc.o: charfunc.h sh_input.h sh_data.h libft.h t_dllst.h
debug.o: sh_parsing.h sh_data.h libft.h token.h
token_utils.o: token.h sh_data.h libft.h
token.o: token.h sh_data.h libft.h quotes.h t_shvar.h
sh_lexing.o: token.h sh_data.h libft.h quotes.h t_shvar.h sh_lexing.h
exec_command.o: t_shvar.h libft.h g_builtins.h sh_data.h sh_parsing.h token.h\
	sh_signals.h
sh_execution.o: sh_execution.h sh_parsing.h sh_data.h libft.h token.h
main.o: sh_input.h sh_data.h libft.h t_dllst.h sh_lexing.h sh_parsing.h\
	token.h sh_execution.h sh_parsing.h
shb_ppt.o: sh_input.h sh_data.h libft.h t_dllst.h sh_lexing.h sh_parsing.h\
	token.h c_colors.h debug.h sh_parsing.h
shb_exit.o: sh_data.h libft.h t_shvar.h
shb_env.o: t_shvar.h libft.h sh_execution.h sh_parsing.h sh_data.h token.h
shb_cd.o: sh_data.h libft.h t_shvar.h
shb_unsetenv.o: t_shvar.h libft.h sh_data.h
shb_unalias.o: t_shvar.h libft.h sh_data.h
shb_alias.o: t_shvar.h libft.h sh_data.h quotes.h
shb_ptok.o: sh_lexing.h sh_data.h libft.h debug.h sh_parsing.h token.h token.h
g_builtins.o: g_builtins.h sh_data.h libft.h
shb_setenv.o: t_shvar.h libft.h sh_data.h
shb_echo.o: sh_data.h libft.h
shb_pwd.o: sh_data.h libft.h t_shvar.h
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
