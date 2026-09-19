// /d/Avakuma/orc/dirty_room.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "Dirty room");
    set("long", @EndText
    This place has been ransacked and then destroyed for its own sake.
The west wall stands, and the corners of the others, and nothing else.
The roof came down some time ago and lies in pieces across the floor.
The odour makes a strong case for going somewhere else.
EndText
    );
    set("item_desc", ([
        "roof" : @EndText
    Roof, what roof? What is left of it is lying on the floor.
EndText
        ,
        "floor" : @EndText
    Dirt, under a covering of everything the roof used to be.
EndText
        ,
        "corners" : @EndText
    The corners of these houses are strong. Often enough they are the
only part left standing.
EndText
        ,
        "walls" : @EndText
    The west wall, and four corners. The rest was pulled down by hand.
EndText
        ,
        "odour" : @EndText
    Reason enough to move along, and there is no getting used to it.
EndText
        ,
        "odor" : @EndText
    Reason enough to move along, and there is no getting used to it.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/orc/dirty_house",
        "north" : "/d/Avakuma/orc/chieftain",
        "south" : "/d/Avakuma/orc/filthy_road_south",
    ]));
    set("exit_order", ({ "east", "north", "south" }));
}
