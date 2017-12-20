/**
 * vimb - a webkit based vim like browser.
 *
 * Copyright (C) 2012-2017 Daniel Carl
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

#include <string.h>

#include "main.h"
#include "handler.h"
#include "util.h"

extern struct Vimb vb;

static char *handler_lookup(Client *c, const char *uri);

void handler_init(Client *c)
{
    c->handlers.table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
}

void handler_cleanup(Client *c)
{
    if (c->handlers.table) {
        g_hash_table_destroy(c->handlers.table);
        c->handlers.table = NULL;
    }
}

gboolean handler_add(Client *c, const char *key, const char *cmd)
{
    g_hash_table_insert(c->handlers.table, g_strdup(key), g_strdup(cmd));

    return TRUE;
}

gboolean handler_remove(Client *c, const char *key)
{
    return g_hash_table_remove(c->handlers.table, key);
}

gboolean handler_handle_uri(Client *c, const char *uri)
{
    char *handler, *cmd;
    GError *error = NULL;
    gboolean res;

    if (!(handler = handler_lookup(c, uri))) {
        return FALSE;
    }

    cmd = g_strdup_printf(handler, uri);
    if (!g_spawn_command_line_async(cmd, &error)) {
        g_warning("Can't run '%s': %s", cmd, error->message);
        g_clear_error(&error);
        res = FALSE;
    } else {
        res = TRUE;
    }

    g_free(cmd);
    return res;
}

gboolean handler_fill_completion(Client *c, GtkListStore *store, const char *input)
{
    GList *src = g_hash_table_get_keys(c->handlers.table);
    gboolean found = util_fill_completion(store, input, src);
    g_list_free(src);

    return found;
}

static char *handler_lookup(Client *c, const char *uri)
{
    char *p, *schema, *handler = NULL;

    if ((p = strchr(uri, ':'))) {
        schema  = g_strndup(uri, p - uri);
        handler = g_hash_table_lookup(c->handlers.table, schema);
        g_free(schema);
    }

    return handler;
}

