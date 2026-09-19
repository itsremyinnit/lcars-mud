// /d/Avakuma/guild/guildmaster.c
// The armchair description carries the siege: the last Guildmaster was
// killed in the orcs' recent push and the post stands empty. This is the
// only room in the area that states it outright.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The Guildmaster's office");
    set("long", @EndText
    The office of the Guildmaster of the Rim-Ainacam. Plush red carpet
runs wall to wall. A few small chairs, well made and plain, stand before
a great solid oak desk, and behind it a black leather armchair with
cushions enough to spare a man's back through a long afternoon. Papers
sit on the desk in neat piles. Paintings cover the walls, and a bookshelf
holds a variety of reading. A lamp on the desk keeps the light warm.
EndText
    );
    set("item_desc", ([
        "carpet" : @EndText
    A smaller cousin of the one in the entrance hall, thick and soft
enough to be almost therapeutic underfoot, with the Guild's crest worked
into it.
EndText
        ,
        "chairs" : @EndText
    The guest chairs are sturdy wood with the Guild's crest carved into
them, and plain otherwise. The leather chair is another matter entirely.
EndText
        ,
        "desk" : @EndText
    A huge oak desk taking up the greater part of the room, stained dark
burgundy and finished smooth. Papers stand in neat piles along the edges,
and an ink pot with a quill in it sits near the back.
EndText
        ,
        "armchair" : @EndText
    The leather chair behind the desk may well be the most comfortable
chair in all of Arda. Supple black leather over a sturdy frame, with soft
cushions on the seat.

    The last Guildmaster of the Rim-Ainacam was killed during the orcs'
recent push on the hall. With the siege on, Framsburg has had no chance
to fill the post, and it is likely there is no longer anyone left with
the skill for it.
EndText
        ,
        "paintings" : @EndText
    Woodland scenes, open country, and portraits of towns, covering most
of the wall.
EndText
        ,
        "bookshelf" : @EndText
    A simple shelf holding a great many books, and old itself by the
look of it.
EndText
        ,
        "lamp" : @EndText
    A lone red crystal lamp on the corner of the desk, with a reservoir
of oil and a wick standing out of it.
EndText
        ,
        "quill" : @EndText
    Standing in the ink pot at the back of the desk, where the last man
to use it left it.
EndText
        ,
    ]));
    set("exits", ([
        "south" : "/d/Avakuma/guild/hallway_2",
    ]));
    set("exit_order", ({ "south" }));
}
