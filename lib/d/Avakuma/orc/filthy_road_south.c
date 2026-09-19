// /d/Avakuma/orc/filthy_road_south.c
// "A filthy cobblestone road" (e, n, sw and ne)
// INFERRED: northeast -> filthy_road_north. Never walked; derived from
// the grid. If this lands somewhere wrong, this is the line.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A filthy cobblestone road");
    set("long", @EndText
PLACEHOLDER. The cobbles continue, but nobody here has cared for them
in a long time. The camp proper lies north.
EndText
    );
    set("exits", ([
        "east"      : "/d/Avakuma/orc/filthy_house",
        "north"     : "/d/Avakuma/orc/dirty_room",
        "southwest" : "/d/Avakuma/orc/battlefield",
        "northeast" : "/d/Avakuma/orc/filthy_road_north",
    ]));
}
