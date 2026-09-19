// /d/Avakuma/framsburg/store.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined store");
    set("long", @EndText
PLACEHOLDER. Broken shelves, a ruined counter, and dust. Whatever was
sold here went with the people who left.
EndText
    );
    set("exits", ([
        "west" : "/d/Avakuma/framsburg/road_south",
    ]));
}
