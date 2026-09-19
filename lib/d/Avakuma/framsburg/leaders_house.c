// /d/Avakuma/framsburg/leaders_house.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "Half of a ruined house");
    set("long", @EndText
PLACEHOLDER. The eastern half has fallen away. What roof remains forms
a canopy over a table. The men's leader keeps here.
EndText
    );
    set("exits", ([
        "east" : "/d/Avakuma/framsburg/kitchen",
    ]));
    set("exit_order", ({ "east" }));
}
