/**
 * vimb - a webkit based vim like browser.
 *
 * Copyright (C) 2012-2015 Daniel Carl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

#ifndef _EX_H
#define _EX_H

#include "config.h"
#include "main.h"

void ex_enter(void);
void ex_leave(void);
VbResult ex_keypress(int key);
void ex_input_changed(const char *text);
gboolean ex_fill_completion(GtkListStore *store, const char *input);
VbCmdResult ex_run_string(const char *input, gboolean enable_history);
VbCmdResult ex_run_file(const char *filename);

#endif /* end of include guard: _EX_H */
