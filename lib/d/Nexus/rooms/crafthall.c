// /d/Nexus/rooms/crafthall.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Crafthall");
    set("long", @EndText
The stone of the concourse bears the marks of making here: chisel lines
left proud in the pillars, and a floor inlaid with bands of copper that
glint in the golden light. To the west a heavy door stands ajar on a room
of workbenches and patient tools. To the east a painted sign hangs above
a doorway crowded with curiosities. North, the hall rises toward a gallery
of banners, and south lies the Commons.
EndText
    );
    set("item_desc", ([
        "copper" : "Bands of copper run the length of the floor, like the grain of a great workbench.\n",
        "sign" : "The painted sign shows a hand holding a lantern. It reads: The Artificer's Stall.\n",
        "door" : "Heavy oak, bound in iron, left open as if someone just stepped out.\n",
    ]));
    set("exits", ([
        "south" : "/d/Nexus/rooms/commons",
        "north" : "/d/Nexus/rooms/hall_of_banners",
        "west"  : "/d/Nexus/rooms/workshop",
        "east"  : "/d/Nexus/rooms/artificers_stall",
    ]));
}
