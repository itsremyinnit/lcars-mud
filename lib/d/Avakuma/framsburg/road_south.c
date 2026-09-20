// /d/Avakuma/framsburg/road_south.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A cobblestone road");
    set("long", @EndText
    This was the main road of the town, and under the grass it still is.
Framsburg must have been pleasant enough once, but nobody has lived here
in years enough for the vegetation to take it back, and the buildings
along both sides are coming apart at their own pace. The one to the east
was a store. From the ruins to the west comes a low murmur of voices.
North the road runs on.
EndText
    );
    set("item_desc", ([
        "road" : @EndText
    Cobbled, and very nearly invisible under the grass.
EndText
        ,
        "vegetation" : @EndText
    It has had its way here, with nobody left to argue.
EndText
        ,
        "buildings" : @EndText
    Walls and roofs alike are full of holes.
EndText
        ,
        "store" : @EndText
    A taller building than its neighbours. A general store, by the look
of what is left.
EndText
        ,
        "ruins" : @EndText
    Not much left of the houses, and voices coming from them all the
same.
EndText
        ,
        "voices" : @EndText
    Men, west of here, keeping their tone down. They are not trying to
be heard.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/store",
        "north" : "/d/Avakuma/framsburg/road_north",
        "west"  : "/d/Avakuma/framsburg/corner_house",
        "south" : "/d/Avakuma/framsburg/entrance",
    ]));
    set("exit_order", ({ "east", "north", "west", "south" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/little_girl" : 1,
    ]));
    spawn_objects();
}
