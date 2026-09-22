#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 8 Port");
    set("long", @EndText
    The corridor has already begun to turn, so that the way you came in
is no longer quite behind you. Doors on the outboard side at intervals,
each with a small panel beside it. One of them has a strip of paper
taped under the panel, which is not a thing this ship does.
EndText
    );
    set("item_desc", ([
        "doors" : @EndText
    Quarters. Each has a name plate beside it at eye height, lit from
within, unremarkable.
EndText
        ,
        "paper" : @EndText
    An actual strip of paper, taped under a door panel, with handwriting
on it: BACK 0600. DO NOT REPROGRAM MY DOOR AGAIN.
EndText
        ,
    ]));
    set("exits", ([
        "east" : "/d/FinalFrontier/deck08/corridor_fore",
        "south" : "/d/FinalFrontier/deck08/corridor_port_aft",
        "quarters" : "/d/FinalFrontier/deck08/quarters_guest",
    ]));
    set("exit_order", ({ "east", "south", "quarters" }));
}
