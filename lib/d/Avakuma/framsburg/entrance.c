// /d/Avakuma/framsburg/entrance.c
// East and west lead out of Framsburg and are deliberately omitted.
// South is sealed as a future expansion. The river along the southern
// edge (the bracketed water exits in the original) is not modelled.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "Entrance to Framsburg");
    set("long", @EndText
PLACEHOLDER. The way into Framsburg from the south. A hitching post
stands here, and a pipe cart. The river runs somewhere below.
EndText
    );
    set("exits", ([
        "north" : "/d/Avakuma/framsburg/road_south",
    ]));
    set("exit_order", ({ "north", "south" }));
    add_sealed("south",
        "The road runs on south out of Framsburg, but not yet.\n");
}
