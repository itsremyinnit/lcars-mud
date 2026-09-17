// /d/Nexus/rooms/hall_of_banners.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Hall of Banners");
    set("long", @EndText
Banners hang in long ranks from the unseen heights, each stirring in a
wind that touches nothing else. Some bear the devices of houses you almost
recognize; most are blank, waiting for names not yet earned. To the east
the ring of practice blades echoes out of the Proving Ground. The western
wall is smooth, unmarked stone, as though the Nexus were keeping the space
for something still to come. The concourse continues north toward a hall
of arches, and south to the Crafthall.
EndText
    );
    set("item_desc", ([
        "banners" : "Long and silent. The blank ones seem, somehow, the most patient.\n",
        "wall" : "The western wall is smooth and bare. It feels like a held breath.\n",
    ]));
    set("exits", ([
        "south" : "/d/Nexus/rooms/crafthall",
        "north" : "/d/Nexus/rooms/concourse_of_arches",
        "east"  : "/d/Nexus/rooms/proving_ground",
    ]));
}
