// /d/Avakuma/orc/end_of_road.c
// "The end of the road" (sw and w)
// INFERRED: southwest -> filthy_road_north. Never walked; west is
// confirmed.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "The end of the road");
    set("long", @EndText
PLACEHOLDER. The road gives up here. Whatever the orcs wanted from
this direction, they stopped wanting it.
EndText
    );
    set("exits", ([
        "southwest" : "/d/Avakuma/orc/filthy_road_north",
        "west"      : "/d/Avakuma/orc/dirty_house",
    ]));
    set("exit_order", ({ "southwest", "west" }));
}
