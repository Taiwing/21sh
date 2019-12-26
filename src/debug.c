/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:27:45 by yforeau           #+#    #+#             */
/*   Updated: 2019/12/26 19:16:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parsing.h"

char * const	g_token_id_str[TOKEN_COUNT + 2] = {
	"I_NEWLINE",
	"I_SEMI",
	"I_AND",
	"I_LESS",
	"I_GREAT",
	"I_PIPE",
	"I_AND_IF",
	"I_OR_IF",
	"I_DLESS",
	"I_DGREAT",
	"I_LESSAND",
	"I_GREATAND",
	"I_LESSGREAT",
	"I_CLOBBER",
	"I_DLESSDASH",
	"I_IO_NUMBER",
	"I_WORD",
	"I_NONE",
	NULL
};

char * const	g_token_type_str[5] = {
	"T_SEPERATOR",
	"T_OPERATOR",
	"T_OTHER",
	"T_NONE",
	NULL
};

char * const g_prod_str[PRODS_COUNT] = {
	"P_COMPLETE_COMMAND",
	"P_LIST",
	"P_LIST_P",
	"P_AND_OR",
	"P_AND_OR_P",
	"P_PIPELINE",
	"P_PIPELINE_P",
	"P_COMMAND",
	"P_CMD_NAME",
	"P_CMD_WORD",
	"P_CMD_PREFIX",
	"P_CMD_SUFFIX",
	"P_IO_REDIRECT",
	"P_IO_FILE",
	"P_FILENAME",
	"P_IO_HERE",
	"P_HERE_END",
	"P_NEWLINE_LIST",
	"P_LINEBREAK",
	"P_SEPARATOR",
	"P_TERM"
};
