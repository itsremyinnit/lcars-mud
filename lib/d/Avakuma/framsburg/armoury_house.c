// /d/Avakuma/framsburg/armoury_house.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A residential area");
    set("long", @EndText
PLACEHOLDER. A ruined house with a weakening frame, an armoury wagon
standing in it.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/road_north",
        "west"  : "/d/Avakuma/framsburg/hospital",
        "wagon" : "/d/Avakuma/framsburg/armoury_wagon",
    ]));
    set("exit_order", ({ "east", "west", "wagon" }));
}
