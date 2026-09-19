// /d/Avakuma/orc/filthy_house.c
// "A filthy house" (n and w)
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A filthy house");
    set("long", @EndText
PLACEHOLDER. An orc dwelling, if it can be called that. A large
campfire burns here.
EndText
    );
    set("exits", ([
        "north" : "/d/Avakuma/orc/filthy_road_north",
        "west"  : "/d/Avakuma/orc/filthy_road_south",
    ]));
    set("exit_order", ({ "north", "west" }));
}
