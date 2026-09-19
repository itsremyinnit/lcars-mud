// /d/Avakuma/guild/conference.c
// The wanted poster is a notice board in the original. Deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A conference room");
    set("long", @EndText
PLACEHOLDER. The guild's conference room. A wanted poster hangs on the
wall. The poster is not yet a working notice board.
EndText
    );
    set("exits", ([
        "west" : "/d/Avakuma/guild/hallway_2",
    ]));
    set("exit_order", ({ "west" }));
    create_door("west", "east", "A heavy door", "closed");
}
