// /d/FinalFrontier/deck08/corridor_fore.c
// The junction. Corridors curve away port and starboard from here and
// arc around the saucer, which is why the exits are cardinal and keep
// turning as you follow them.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 8 Forward");
    set("long", @EndText
    The corridor forks here, one arm curving away to port and the other
to starboard, both of them bending out of sight within thirty feet. A
directory panel is set into the bulkhead between them. The carpet is the
same grey as everywhere else and the light band runs on in both
directions. Somewhere down the port arm a door cycles and somebody
laughs, once.
EndText
    );
    set("item_desc", ([
        "panel" : @EndText
    A deck directory. Quarters numbered 0801 through 0812 to port, 0813
through 0824 to starboard. Four names on this deck have been updated
recently enough that the lettering is a slightly different grey.
EndText
        ,
        "band" : "    The light strip, running off in both directions and curving out of sight.\n",
        "carpet" : "    Grey, clean, and quiet underfoot. It is the same carpet on every deck.\n",
    ]));
    set("exits", ([
        "east" : "/d/FinalFrontier/deck08/corridor_port",
        "west" : "/d/FinalFrontier/deck08/corridor_starboard",
        "lift" : "/d/FinalFrontier/deck08/turbolift",
    ]));
    set("exit_order", ({ "east", "west", "lift" }));

    set("objects", ([
        "/d/FinalFrontier/npc/crewman" : 1,
    ]));
    spawn_objects();
}
