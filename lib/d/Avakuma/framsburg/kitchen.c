// /d/Avakuma/framsburg/kitchen.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined house that has a smell of stew all about it");
    set("long", @EndText
PLACEHOLDER. Curtains, a rug over the dirt, a pot over the fire, and a
menu on the wall. The menu is not yet functional.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/corner_house",
        "north" : "/d/Avakuma/framsburg/hospital",
        "west"  : "/d/Avakuma/framsburg/leaders_house",
    ]));
    set("exit_order", ({ "east", "north", "west" }));
}
