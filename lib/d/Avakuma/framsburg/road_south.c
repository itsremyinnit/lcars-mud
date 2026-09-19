// /d/Avakuma/framsburg/road_south.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A cobblestone road");
    set("long", @EndText
PLACEHOLDER. The main road of the town, vegetation taking it back. A
store east, voices from the ruins west, the town entrance south.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/store",
        "north" : "/d/Avakuma/framsburg/road_north",
        "west"  : "/d/Avakuma/framsburg/corner_house",
        "south" : "/d/Avakuma/framsburg/entrance",
    ]));
    set("exit_order", ({ "east", "north", "west", "south" }));
}
