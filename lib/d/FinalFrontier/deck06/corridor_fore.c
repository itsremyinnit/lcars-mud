#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 6 Forward");
    set("long", @EndText
    A working corridor rather than a residential one: wider, with tie-down
points along the deck and scuff marks on the bulkheads at cargo height.
The transporter room is off to port. The corridor runs aft and begins its
turn almost immediately.
EndText
    );
    set("item_desc", ([
        "scuffs" : @EndText
    Long grey marks along the bulkhead at about waist height, the whole
length of the corridor. Something wide has been walked down here many
times and not always carefully.
EndText
        ,
        "points" : @EndText
    Recessed tie-downs set into the deck at intervals, flush when not in
use. Two of them have been left up.
EndText
        ,
    ]));
    set("exits", ([
        "southeast"   : "/d/FinalFrontier/deck06/corridor_mid",
        "transporter" : "/d/FinalFrontier/deck06/transporter",
        "lift"        : "/d/FinalFrontier/deck06/turbolift",
    ]));
    set("exit_order", ({ "southeast", "transporter", "lift" }));
}
