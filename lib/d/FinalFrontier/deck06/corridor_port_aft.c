// /d/FinalFrontier/deck06/corridor_port_aft.c
// Closes the deck 6 loop and carries the aft turbolift.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 6 Port Aft");
    set("long", @EndText
    The corridor comes round the back of the deck here and runs on toward
the forward section. Cargo control opens off to starboard and the aft
turbolift stands opposite it. The scuff marks along the bulkhead are worse
along this stretch than anywhere else, which tells you which way the heavy
things get walked.
EndText
    );
    set("item_desc", ([
        "scuffs" : @EndText
    Deeper here, and in places gouged rather than scuffed. Whatever comes
out of that bay comes this way and does not always fit.
EndText
        ,
    ]));
    set("exits", ([
        "north"    : "/d/FinalFrontier/deck06/corridor_fore",
        "east"     : "/d/FinalFrontier/deck06/corridor_aft",
        "cargo"    : "/d/FinalFrontier/deck06/cargo_control",
        "lift"     : "/d/FinalFrontier/deck06/turbolift_aft",
    ]));
    set("exit_order", ({ "north", "east", "cargo", "lift" }));
}
