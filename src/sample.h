/*
 * Sweep, a sound wave editor.
 *
 * Copyright (C) 2000 Conrad Parker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "sweep_types.h"
#include "sweep_app.h"

sw_sdata *
sdata_new_empty(char * directory, char * filename,
		gint nr_channels, gint sample_rate, gint sample_length);

void
sdata_destroy (sw_sdata * sdata);

sw_sample *
sample_new_empty(char * directory, char * filename,
		 gint nr_channels, gint sample_rate, gint sample_length);

sw_sample *
sample_new_copy(sw_sample * s);

void
sample_add_view (sw_sample * s, sw_view * v);

void
sample_remove_view (sw_sample * s, sw_view * v);

void
sample_destroy (sw_sample * s);

void
sample_set_pathname (sw_sample * s, char * directory, char * filename);

void
sample_bank_add (sw_sample * s);

void
sample_bank_remove (sw_sample * s);

void
sample_refresh_views (sw_sample * s);

void
sample_set_playmarker (sw_sample * s, int offset);

/*
 * sample_replace_throughout (os, s)
 *
 * Replaces os with s throughout the program, ie:
 *   - in the sample bank
 *   - in all os's views
 *
 * Destroys os.
 *
 */
void
sample_replace_throughout (sw_sample * os, sw_sample * s);


/* Selection handling */

guint
sample_sel_nr_regions (sw_sample * s);

void
sdata_clear_selection (sw_sdata * sdata);

void
sample_clear_selection (sw_sample * s);

void
sdata_add_selection (sw_sdata * sdata, sw_sel * sel);

void
sample_add_selection (sw_sample * s, sw_sel * sel);

sw_sel *
sdata_add_selection_1 (sw_sdata * sdata, glong start, glong end);

sw_sel *
sample_add_selection_1 (sw_sample * s, glong start, glong end);

void
sample_set_selection (sw_sample * s, GList * gl);

sw_sel *
sdata_set_selection_1 (sw_sdata * sdata, glong start, glong end);

sw_sel *
sample_set_selection_1 (sw_sample * s, glong start, glong end);


/* Modify a given existing selection */
void
sel_modify (sw_sample * s, sw_sel * sel, glong new_start, glong new_end);

void
sample_selection_invert (sw_sample * s);

void
sample_selection_select_all (sw_sample * s);

void
sample_selection_select_none (sw_sample * s);

gint
sdata_selection_length (sw_sdata * sdata);

void
sdata_selection_translate (sw_sdata * sdata, gint delta);

/*
 * sdata_copyin_selection (sdata, sdata2)
 *
 * copies the selection of sdata1 into sdata2. If sdata2 previously
 * had a selection, the two are merged.
 */
void
sdata_copyin_selection (sw_sdata * sdata1, sw_sdata * sdata2);

/*
 * sel_replace: undo/redo functions for changing selection
 */

typedef struct _sel_replace_data sel_replace_data;

struct _sel_replace_data {
  GList * sels;
};

sel_replace_data *
sel_replace_data_new (GList * sels);

void
sel_replace_data_destroy (sel_replace_data * s);

void
do_by_sel_replace (sw_sample * s, sel_replace_data * sr);


/*
 * Functions to handle the temporary selection.
 */

void
sample_clear_tmp_sel (sw_sample * s);

/* sample_set_tmp_sel (s, tsel)
 *
 * sets the tmp_sel of sample s to a list containing only tsel.
 * If tsel was part of the actual selection of s, it is first
 * removed from the selection.
 */
void
sample_set_tmp_sel (sw_sample * s, sw_view * tview, sw_sel * tsel);

void
sample_set_tmp_sel_1 (sw_sample * s, sw_view * tview, glong start, glong end);

void
sample_selection_insert_tmp_sel (sw_sample * s);

void
sample_selection_replace_with_tmp_sel (sw_sample * s);

#endif /* __SAMPLE_H__ */
