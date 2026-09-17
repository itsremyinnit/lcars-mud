// /d/Nexus/rooms/workshop.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Workshop");
    set("long", @EndText
Long workbenches fill this room, scarred and scorched and entirely
beloved, and tools hang in neat rows along the walls, each within easy
reach of wherever you happen to be standing. Half-finished things wait on
the benches: a clockwork bird missing a wing, a map that redraws itself,
a door frame leaning against the wall with no door and nowhere to go yet.
It is the kind of place where good ideas happen by accident. The Crafthall
lies back to the east.
EndText
    );
    set("item_desc", ([
        "benches" : "Scarred, scorched, and patiently waiting for the next idea.\n",
        "tools" : "Hammers, chisels, and a few instruments whose purpose is not immediately clear.\n",
        "bird" : "A clockwork bird with one wing. It turns its head to watch you.\n",
        "map" : "As you look, a new corridor inks itself onto the map, then politely fades.\n",
        "door frame" : "A door frame with no door. It looks like it's waiting for somewhere to lead.\n",
    ]));
    set("exits", ([
        "east" : "/d/Nexus/rooms/crafthall",
    ]));
}
