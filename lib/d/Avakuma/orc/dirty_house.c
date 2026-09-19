// /d/Avakuma/orc/dirty_house.c
// "A dirty house" (e, w and s) - the orc counterpart to Framsburg's
// hospital: injured orcs and a medic.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A dirty house");
    set("long", @EndText
PLACEHOLDER. Where the orcs put their wounded. The mirror of the
hospital across the battlefield, and no better kept.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/orc/end_of_road",
        "west"  : "/d/Avakuma/orc/dirty_room",
        "south" : "/d/Avakuma/orc/filthy_road_north",
    ]));
    set("exit_order", ({ "east", "west", "south" }));
}
