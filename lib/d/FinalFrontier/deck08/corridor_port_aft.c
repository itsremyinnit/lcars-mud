#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 8 Port Aft");
    set("long", @EndText
    Still turning. By now the curve has brought you around far enough
that the corridor ahead looks exactly like the corridor behind, and only
the numbers beside the doors tell you which way you are facing. A cat
sits in the middle of the deck, orange, entirely at ease, watching you
with the flat interest of something that has decided you are not
interesting.
EndText
    );
    set("item_desc", ([
        "cat" : @EndText
    Orange, short-haired, sitting square in the middle of the corridor
with its tail wrapped around its feet. It has a collar. It does not move
when you approach, on the grounds that it was here first.
EndText
        ,
        "collar" : @EndText
    A plain band with a small tag. The tag says SPOT, and beneath that,
DECK 2, QUARTERS 2517, and beneath that, in smaller lettering: SHE IS
NOT LOST. SHE IS RETURNING.
EndText
        ,
        "doors" : "    More quarters, their numbers climbing as the corridor turns.\n",
    ]));
    set("exits", ([
        "northwest" : "/d/FinalFrontier/deck08/corridor_port",
        "south"     : "/d/FinalFrontier/deck08/corridor_aft",
    ]));
    set("exit_order", ({ "northwest", "south" }));
}
