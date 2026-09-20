#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 8 Aft");
    set("long", @EndText
    The two arms meet again here at the back of the saucer, which means
you have walked a complete circle without once turning a corner. There is
a viewport in the outboard bulkhead, the first one you have seen on this
deck, and through it the nacelles hold their steady blue a long way off.
Somebody has pulled a chair up to it.
EndText
    );
    set("item_desc", ([
        "viewport" : @EndText
    A single port in the outboard wall, waist to head height. The
nacelles are visible from here, and a great deal of nothing else.
EndText
        ,
        "chair" : @EndText
    A chair from somebody's quarters, carried out here and left facing
the viewport. It has been here long enough that the carpet under it has
stopped springing back.
EndText
        ,
        "nacelles" : "    Blue, steady, and further away than the ship feels from the inside.\n",
    ]));
    set("exits", ([
        "north"     : "/d/FinalFrontier/deck08/corridor_port_aft",
        "northeast" : "/d/FinalFrontier/deck08/corridor_starboard",
        "lift"      : "/d/FinalFrontier/deck08/turbolift_aft",
    ]));
    set("exit_order", ({ "north", "northeast", "lift" }));
}
