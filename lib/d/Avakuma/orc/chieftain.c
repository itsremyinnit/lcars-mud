// /d/Avakuma/orc/chieftain.c
// "A house in nice shape" (e and s) - the only sound building in the
// camp, which is the joke.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A house in nice shape");
    set("long", @EndText
PLACEHOLDER. The one building in the camp that anyone has bothered to
maintain. The orc chieftain holds it.
EndText
    );
    set("exits", ([
        "east" : "/d/Avakuma/orc/dirty_house",
        "south" : "/d/Avakuma/orc/dirty_room",
    ]));
    set("exit_order", ({ "east", "south" }));
}
