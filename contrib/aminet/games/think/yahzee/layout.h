/*
 * layout.h
 * ========
 * Interface to display layout functions.
 *
 * Copyright (C) 1994-1998 H�kan L. Younes (lorens@hem.passagen.se)
 */

#include <exec/types.h>

BOOL
layout_display (
   struct Screen  *scr,
   struct Window **win,
   const struct rules   *rules,
   UBYTE           num_players);

void
init_board_grid (
   struct Window  *win,
   const struct rules   *rules,
   UBYTE           num_players,
   BOOL            split_board);
