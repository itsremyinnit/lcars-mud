// /d/Avakuma/framsburg/barracks.c
// The north door is a real door object in the original, locked from the
// far side, with authored bash and pick refusals. Sealed for now; the
// door object and the interior are deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "Entrance to the guard barracks");
    set("long", @EndText
PLACEHOLDER. The barracks of the Framsburg guard, recently built and
well kept. The front door is large and firmly closed. A sign hangs
beside it, and the path to the door is badly worn.
EndText
    );
    set("exits", ([
        "south" : "/d/Avakuma/framsburg/hospital",
    ]));
    add_sealed("north",
        "The door is locked.\n");
}
