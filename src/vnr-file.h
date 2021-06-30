/*
 * Copyright © 2009-2018 Siyan Panayotov <contact@siyanpanayotov.com>
 *
 * This file is part of Viewnior.
 *
 * Viewnior is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Viewnior is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Viewnior.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __VNR_FILE_H__
#define __VNR_FILE_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define VNR_TYPE_FILE            (vnr_file_get_type ())
#define VNR_FILE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), VNR_TYPE_FILE, VnrFile))
#define VNR_FILE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), VNR_TYPE_FILE, VnrFileClass))
#define VNR_IS_FILE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), VNR_TYPE_FILE))
#define VNR_IS_FILE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), VNR_TYPE_FILE))
#define VNR_FILE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), VNR_TYPE_FILE, VnrFileClass))

typedef enum {
    SORT_ASC   = 0,
    SORT_DESC  = 1<<8
} SortDirection;

typedef enum {
    SORT_NONE               = 0,

    SORT_DISPLAY_NAME       = 1<<1              | SORT_ASC,
    SORT_MOD_TIME           = 1<<2              | SORT_ASC,
    SORT_SIZE               = 1<<3              | SORT_ASC,
    SORT_TYPE               = 1<<4              | SORT_ASC,

    SORT_DISPLAY_NAME_DESC  = SORT_DISPLAY_NAME | SORT_DESC,
    SORT_MOD_TIME_DESC      = SORT_MOD_TIME     | SORT_DESC,
    SORT_SIZE_DESC          = SORT_SIZE         | SORT_DESC,
    SORT_TYPE_DESC          = SORT_TYPE         | SORT_DESC
} SortType;

typedef struct _VnrFile VnrFile;
typedef struct _VnrFileClass VnrFileClass;

struct _VnrFile {
    GObject parent;

    const gchar *display_name;
    const gchar *display_name_collate;
    const GDateTime *mod_time;
    goffset size;
    const gchar *path;
};

struct _VnrFileClass {
    GObjectClass parent;
};

GType   vnr_file_get_type   (void) G_GNUC_CONST;

/* Constructors */
VnrFile *vnr_file_new ();

/* Actions */
void    vnr_file_load_uri_list      (GSList *uri_list, GList **file_list, gboolean include_hidden, SortType sort_type, GError **error);
void    vnr_file_load_single_uri    (char *p_uri, GList **file_list, gboolean include_hidden, SortType sort_type, GError **error);
GList   *vnr_file_list_sort         (GList *file_list, gint sort);

G_END_DECLS

#endif /* __VNR_FILE_H__ */
