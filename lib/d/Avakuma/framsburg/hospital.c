// /d/Avakuma/framsburg/hospital.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A residential area");
    set("long", @EndText
PLACEHOLDER. The soundest roof in Framsburg. The men use this ruin as
a hospital of sorts.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/armoury_house",
        "north" : "/d/Avakuma/framsburg/barracks",
        "south" : "/d/Avakuma/framsburg/kitchen",
    ]));
    set("exit_order", ({ "east", "north", "south" }));
}
