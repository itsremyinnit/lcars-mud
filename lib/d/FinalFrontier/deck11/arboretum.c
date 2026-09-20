// /d/FinalFrontier/deck11/arboretum.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "The Arboretum");
    set("long", @EndText
    Warm, humid, and loud with water. Paths run between beds of things
from a dozen worlds, arranged by nobody's taxonomy but somebody's eye,
and the lighting overhead is running a slow cycle that is presently
somewhere around late afternoon. There are benches. At the far end, a
work table with pots stacked on it and soil on the surface, swept into a
pile but not cleared away.
EndText
    );
    set("item_desc", ([
        "beds" : @EndText
    Plants from a dozen worlds, none of them labelled in any order that
makes botanical sense. Two from the same system are at opposite ends of
the room; two that could not be less related are side by side and doing
well.
EndText
        ,
        "table" : @EndText
    A work surface at the far end, soil swept into a pile and left. Empty
clay pots stacked beside it, the same rough red clay throughout.
EndText
        ,
        "pots" : @EndText
    Clay, hand-thrown rather than replicated, a dozen of them. One near
the bottom of the stack has a chip out of the rim that has been smoothed
down rather than repaired.
EndText
        ,
        "benches" : @EndText
    Two, facing the beds rather than each other. The one nearer the water
has been used more.
EndText
        ,
        "lighting" : @EndText
    A full day in something over two hours. At the moment it is late
afternoon in here, and has been for twenty minutes.
EndText
        ,
        "water" : @EndText
    A channel running the length of the room, shallow and moving. It is
the loudest thing on this deck.
EndText
        ,
    ]));
    set("exits", ([
        "forward" : "/d/FinalFrontier/deck11/corridor",
    ]));
    set("exit_order", ({ "forward" }));
}
