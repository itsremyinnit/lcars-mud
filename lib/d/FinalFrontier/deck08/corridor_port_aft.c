#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 8 Port Aft");
    set("long", @EndText
    Still turning. By now the curve has brought you around far enough
that the corridor ahead looks exactly like the corridor behind, and only
the numbers beside the doors tell you which way you are facing. There
are faint orange hairs along the base of the bulkhead, which on this
deck is not unusual.
EndText
    );
    set("item_desc", ([
        "hairs" : @EndText
    Orange, short, along the base of the bulkhead. Somebody small and
furred walks this deck regularly and considers it hers.
EndText
        ,
        "doors" : "    More quarters, their numbers climbing as the corridor turns.\n",
    ]));
    set("exits", ([
        "north" : "/d/FinalFrontier/deck08/corridor_port",
        "southeast" : "/d/FinalFrontier/deck08/corridor_aft",
    ]));
    set("exit_order", ({ "north", "southeast" }));

    set("objects", ([
        "/d/FinalFrontier/npc/spot" : 1,
    ]));
    spawn_objects();
}
