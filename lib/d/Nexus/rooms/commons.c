// /d/Nexus/rooms/commons.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Commons");
    set("long", @EndText
Here the great hall gathers itself into a crossroads of quiet purpose.
Benches of dark wood stand between the pillars, and the air carries the
scent of old paper from the west, where tall shelves rise beyond an open
archway. From the east comes the rustle of wings and the soft clatter of
messages arriving from far places. The concourse runs on to the north and
back to the south.
EndText
    );
    set("item_desc", ([
        "benches" : "Dark wood, polished by long use, though no one remembers sitting here.\n",
        "shelves" : "They rise to the west, higher than seems reasonable.\n",
        "wings" : "Beyond the eastern door, something feathered settles and resettles.\n",
    ]));
    set("exits", ([
        "south" : "/d/Nexus/rooms/grand_concourse",
        "north" : "/d/Nexus/rooms/crafthall",
        "west"  : "/d/Nexus/rooms/hall_of_records",
        "east"  : "/d/Nexus/rooms/rookery",
    ]));
}
