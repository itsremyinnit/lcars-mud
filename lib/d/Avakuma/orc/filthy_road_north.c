// /d/Avakuma/orc/filthy_road_north.c
// "A filthy road" (sw, n, w, s and ne)
// INFERRED: southwest -> filthy_road_south. Never walked.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A filthy road");
    set("long", @EndText
PLACEHOLDER. The heart of the orc camp, such as it is. Roads lead off
in every direction and none of them are clean.
EndText
    );
    set("exits", ([
        "southwest" : "/d/Avakuma/orc/filthy_road_south",
        "north"     : "/d/Avakuma/orc/dirty_house",
        "west"      : "/d/Avakuma/orc/dirty_room",
        "south"     : "/d/Avakuma/orc/filthy_house",
        "northeast" : "/d/Avakuma/orc/end_of_road",
    ]));
    set("exit_order", ({ "southwest", "north", "west", "south", "northeast" }));
}
