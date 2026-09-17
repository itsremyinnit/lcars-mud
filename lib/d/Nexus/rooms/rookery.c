// /d/Nexus/rooms/rookery.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Rookery");
    set("long", @EndText
Perches line this tall, round room from floor to rafters, and messenger
birds of every kind doze, preen, and bicker upon them: ravens and owls,
swift grey falcons, and one small, very determined sparrow. Pigeonholes
of polished wood fill one wall, each labeled in a careful hand, and the
air is full of soft wingbeats and the dry rustle of letters. The Commons
lies back to the west.
EndText
    );
    set("item_desc", ([
        "birds" : "They eye you with polite professional interest.\n",
        "sparrow" : "It looks back at you as if it would carry a boulder across the world if asked.\n",
        "pigeonholes" : "Most are empty. A few already have names written beneath them.\n",
        "perches" : "Worn smooth by claws, rising all the way into the rafters.\n",
    ]));
    set("exits", ([
        "west" : "/d/Nexus/rooms/commons",
    ]));
}
