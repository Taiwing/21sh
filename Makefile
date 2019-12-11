############################## COMPILE VAR #####################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		=	-g
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

SRCC			=	main.c\
					ms_init.c\

BUILTINSC		=	g_builtins.c\
					msb_alias.c\
					msb_cd.c\
					msb_echo.c\
					msb_env.c\
					msb_exit.c\
					msb_pwd.c\
					msb_setenv.c\
					msb_unalias.c\
					msb_unsetenv.c\

EXECUTIONC		=	exec.c\
					ms_execution.c\

GLOBALC			=	env.c\
					history.c\
					ms_signals.c\
					quotes.c\
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
					ms_input.c\
					tab_completion.c\
					terminal_cursor.c\

LEXINGC			=	ms_lexing.c\
					token.c\

PARSINGC		=	ms_parsing.c\
					param_exp.c\
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
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS)

$(SUB1D)/libft.a:
	make -C $(SUB1D)

g_builtins.o: g_builtins.h ms_data.h libft.h
msb_alias.o: t_shvar.h libft.h ms_data.h quotes.h
msb_cd.o: ms_data.h libft.h t_shvar.h
msb_echo.o: ms_data.h libft.h
msb_env.o: t_shvar.h libft.h ms_execution.h ms_data.h
msb_exit.o: ms_data.h libft.h t_shvar.h
msb_pwd.o: ms_data.h libft.h t_shvar.h
msb_setenv.o: t_shvar.h libft.h ms_data.h
msb_unalias.o: t_shvar.h libft.h ms_data.h
msb_unsetenv.o: t_shvar.h libft.h ms_data.h
exec.o: ms_data.h libft.h t_shvar.h ms_signals.h
ms_execution.o: exec.h ms_data.h libft.h g_builtins.h ms_execution.h
env.o: t_shvar.h libft.h
history.o: ms_data.h libft.h
ms_signals.o: libft.h terminal_size.h terminal_cursor.h
quotes.o: quotes.h libft.h
t_shvar_list.o: t_shvar.h libft.h
t_shvar_utils.o: t_shvar.h libft.h
char_functions_1.o: charfunc.h ms_input.h ms_data.h libft.h t_dllst.h quotes.h\
	tab_completion.h
char_functions_2.o: charfunc.h ms_input.h ms_data.h libft.h t_dllst.h\
	input_history.h
char_functions_3.o: charfunc.h ms_input.h ms_data.h libft.h t_dllst.h
charfunc.o: charfunc.h ms_input.h ms_data.h libft.h t_dllst.h
charfunc_utils.o: charfunc.h ms_input.h ms_data.h libft.h t_dllst.h quotes.h
completion_utils.o: libft.h
dllst_insert.o: t_dllst.h libft.h
dllst_move.o: t_dllst.h libft.h
dllst_remove.o: t_dllst.h libft.h
dllst_str.o: t_dllst.h libft.h
env_completion.o: tab_completion.h ms_input.h ms_data.h libft.h t_dllst.h\
	t_shvar.h
exec_completion.o: tab_completion.h ms_input.h ms_data.h libft.h t_dllst.h\
	g_builtins.h
file_completion.o: tab_completion.h ms_input.h ms_data.h libft.h t_dllst.h
input_history.o: ms_input.h ms_data.h libft.h t_dllst.h charfunc.h\
	terminal_cursor.h
ms_input.o: charfunc.h ms_input.h ms_data.h libft.h t_dllst.h quotes.h\
	t_shvar.h c_colors.h terminal_size.h terminal_cursor.h
tab_completion.o: tab_completion.h ms_input.h ms_data.h libft.h t_dllst.h\
	charfunc.h quotes.h terminal_cursor.h
terminal_cursor.o: libft.h ms_input.h ms_data.h t_dllst.h
ms_lexing.o: token.h ms_data.h libft.h quotes.h t_shvar.h ms_lexing.h
token.o: token.h ms_data.h libft.h quotes.h t_shvar.h
main.o: ms_input.h ms_data.h libft.h t_dllst.h ms_lexing.h ms_parsing.h\
	ms_execution.h
ms_init.o: ms_data.h libft.h t_shvar.h ms_signals.h terminal_size.h
ms_parsing.o: token.h ms_data.h libft.h tilde_exp.h param_exp.h quotes.h
param_exp.o: ms_data.h libft.h quotes.h t_shvar.h
tilde_exp.o: ms_data.h libft.h t_shvar.h
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
