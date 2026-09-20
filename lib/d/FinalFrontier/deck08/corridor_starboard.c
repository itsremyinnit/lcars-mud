#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 8 Starboard");
    set("long", @EndText
    The mirror of the port arm, bending the other way. Doors on the
outboard side, panels beside them, the same grey carpet. A maintenance
hatch stands open low in the inboard bulkhead with a toolkit beside it
and nobody in attendance.
EndText
    );
    set("item_desc", ([
        "hatch" : @EndText
    An access panel, open, showing a crawlway running inboard and down.
Whatever is in there is too far along the tube to see.
EndText
        ,
        "toolkit" : @EndText
    Open, laid out neatly, one spanner missing from its slot. Beside it,
a padd showing a work order: PLASMA CONDUIT INSPECTION, DECK 11. Somebody
started here and went somewhere else.
EndText
        ,
        "doors" : "    Quarters, numbered upward as the corridor curves.\n",
    ]));
    set("exits", ([
        "east"      : "/d/FinalFrontier/deck08/corridor_fore",
        "southwest" : "/d/FinalFrontier/deck08/corridor_aft",
    ]));
    set("exit_order", ({ "east", "southwest" }));
}
