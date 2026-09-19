// /d/Avakuma/orc/filthy_road_north.c
// INFERRED: southwest -> filthy_road_south. Never walked in the original.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A filthy road");
    set("long", @EndText
    The stink here is considerable, something in the order of sweat and
manure together. Houses stand in shambles on every side, which makes this
as good a place to lie up in as any in the region. The road goes on
northeast and southwest.
EndText
    );
    set("item_desc", ([
        "road" : "    A dirty cobblestone road.\n",
        "houses" : @EndText
    They would be in poor shape if nobody had touched them. Somebody has
been making a project of wrecking them further.
EndText
        ,
        "smell" : @EndText
    Sweat and manure, and underneath that something worse that does not
bear identifying.
EndText
        ,
        "shambles" : @EndText
    Every house on the road, and useful in that state. A man could hide
in any of them.
EndText
        ,
    ]));
    set("exits", ([
        "southwest" : "/d/Avakuma/orc/filthy_road_south",
        "north"     : "/d/Avakuma/orc/dirty_house",
        "west"      : "/d/Avakuma/orc/dirty_room",
        "south"     : "/d/Avakuma/orc/filthy_house",
        "northeast" : "/d/Avakuma/orc/end_of_road",
    ]));
    set("exit_order", ({ "southwest", "north", "west", "south", "northeast" }));
}
