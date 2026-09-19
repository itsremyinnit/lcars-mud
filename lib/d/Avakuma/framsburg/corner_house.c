// /d/Avakuma/framsburg/corner_house.c
// Outdoors: ruined enough that weather prints here. Confirmed from the
// verbose walk, which showed sky and wind lines in this room.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A residential district");
    set("long", @EndText
PLACEHOLDER. Four corners of a house that was fine once. More shelter
than nothing at all, but not by much.
EndText
    );
    set("exits", ([
        "east" : "/d/Avakuma/framsburg/road_south",
        "west" : "/d/Avakuma/framsburg/kitchen",
    ]));
    set("exit_order", ({ "east", "west" }));
}
