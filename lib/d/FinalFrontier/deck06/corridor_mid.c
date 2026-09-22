#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 6");
    set("long", @EndText
    The corridor turns and keeps turning. Doors along the outboard side
here are unmarked and sealed, their panels dark: compartments that were
allocated and never fitted out, of which this ship apparently has
several. The light band runs on. Aft, the corridor continues.
EndText
    );
    set("item_desc", ([
        "doors" : @EndText
    Four of them, unmarked, panels dark. Behind each is a compartment
that was framed, wired, and then left. Somebody's plans for this deck
changed.
EndText
        ,
        "panels" : @EndText
    Dark, but not dead: hold a hand near one and it lights faintly and
shows a compartment number and the word UNASSIGNED.
EndText
        ,
    ]));
    set("exits", ([
        "northwest" : "/d/FinalFrontier/deck06/corridor_fore",
        "south"     : "/d/FinalFrontier/deck06/corridor_aft",
    ]));
    set("exit_order", ({ "northwest", "south" }));

    set("objects", ([
        "/d/FinalFrontier/npc/crewman" : 1,
    ]));
    spawn_objects();
}
