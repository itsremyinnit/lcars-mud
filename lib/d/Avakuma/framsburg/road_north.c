// /d/Avakuma/framsburg/road_north.c
// Exit order in the mapping literal drives the order in the brief-mode
// parenthesised list. Kept as east, north, west, south to match the
// original.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A cobblestone road");
    set("long", @EndText
PLACEHOLDER. The northern stretch of cobblestone road, grass coming
up through it. The pub lies east, houses west, the battlefield north.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/pub",
        "north" : "/d/Avakuma/orc/battlefield",
        "west"  : "/d/Avakuma/framsburg/armoury_house",
        "south" : "/d/Avakuma/framsburg/road_south",
    ]));
    set("exit_order", ({ "east", "north", "west", "south" }));
}
