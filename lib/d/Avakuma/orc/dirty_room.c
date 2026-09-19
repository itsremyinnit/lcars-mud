// /d/Avakuma/orc/dirty_room.c
// "Dirty room" (e, n and s)
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "Dirty room");
    set("long", @EndText
PLACEHOLDER. A room, and it is dirty. The chieftain keeps north of
here.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/orc/dirty_house",
        "north" : "/d/Avakuma/orc/chieftain",
        "south" : "/d/Avakuma/orc/filthy_road_south",
    ]));
}
