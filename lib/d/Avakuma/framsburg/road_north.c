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
    The cobbles are losing ground to the grass, and in places the road
is more guess than surface. Buildings line it east and west, all of
them coming apart at their own pace, though the one to the east was
plainly a pub and has kept enough of itself to say so. Footprints go
west through the grass toward a row of ruined houses, and they are not
old. North and south the road runs on.
EndText
    );
    set("item_desc", ([
        "grass" : @EndText
    Thick enough here to swallow the road. Where it grows heaviest
there is no telling stone from ground.
EndText
        ,
        "road" : @EndText
    Stones the size of a closed fist, set close and worn smooth on top.
Whoever laid them meant the road to outlast the town, and so far it has.
EndText
        ,
        "cobblestone" : @EndText
    Stones the size of a closed fist, set close and worn smooth on top.
Whoever laid them meant the road to outlast the town, and so far it has.
EndText
        ,
        "buildings" : @EndText
    Barely the word for them now. Roofs open to the sky, walls standing
out of habit.
EndText
        ,
        "footprints" : @EndText
    Human, and pressed deep enough in the wet ground to be recent. They
lead west and do not come back.
EndText
        ,
        "houses" : @EndText
    Not much left of any of them, though a wall and a corner of roof
still beat standing in the open.
EndText
        ,
        "pub" : @EndText
    Built differently to everything around it, all timber where the
houses are stone, and standing a storey taller. It has come through
better for it.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/pub",
        "north" : "/d/Avakuma/orc/battlefield",
        "west"  : "/d/Avakuma/framsburg/armoury_house",
        "south" : "/d/Avakuma/framsburg/road_south",
    ]));
    set("exit_order", ({ "east", "north", "west", "south" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/intimidating_guard" : 1,
        "/d/Avakuma/framsburg/npc/little_boy" : 1,
    ]));
    spawn_objects();
}
