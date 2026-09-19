// /d/Avakuma/guild/supply_room.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The Guild's supply room");
    set("long", @EndText
PLACEHOLDER. The guild's supply room. A sheriff in training practises
here while Eomon watches.
EndText
    );
    set("exits", ([
        "north" : "/d/Avakuma/guild/hallway_2",
    ]));
    set("exit_order", ({ "north" }));
}
