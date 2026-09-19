// /d/Avakuma/orc/battlefield.c
// The seam between Framsburg and the orc camp.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A battlefield");
    set("long", @EndText
PLACEHOLDER. The ground between the town and the orc camp. Whatever
was fought over here, both sides are still close enough to try again.
EndText
    );
    set("exits", ([
        "northeast" : "/d/Avakuma/orc/filthy_road_south",
        "south"     : "/d/Avakuma/framsburg/road_north",
    ]));
    set("exit_order", ({ "northeast", "south" }));
}
