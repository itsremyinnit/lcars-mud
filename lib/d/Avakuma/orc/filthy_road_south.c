// /d/Avakuma/orc/filthy_road_south.c
// INFERRED: northeast -> filthy_road_north. Never walked in the original.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "A filthy cobblestone road");
    set("long", @EndText
    The cobbled road runs southwest and northeast. The ground here is
much as it is throughout Framsburg, but there is a smell on the air that
argues for leaving. North and east stand run-down houses, and they are
lived in, though not by men.
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
    Something between a midden and a wet dog, and it gets stronger to
the northeast.
EndText
        ,
        "terrain" : @EndText
    The same ground Framsburg stands on. Only the tenants have changed.
EndText
        ,
    ]));
    set("exits", ([
        "east"      : "/d/Avakuma/orc/filthy_house",
        "north"     : "/d/Avakuma/orc/dirty_room",
        "southwest" : "/d/Avakuma/orc/battlefield",
        "northeast" : "/d/Avakuma/orc/filthy_road_north",
    ]));
    set("exit_order", ({ "east", "north", "southwest", "northeast" }));
}
