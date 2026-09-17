// /d/Nexus/rooms/artificers_stall.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Artificer's Stall");
    set("long", @EndText
Every surface in this cramped and cheerful shop holds something curious:
shelves of stoppered bottles glowing faintly, drawers labeled in languages
no one speaks anymore, and a rack of walking sticks that seem to lean
toward whoever enters. A wide counter of dark wood stands at the back with
a small brass bell upon it, though the proprietor appears to be out for
the moment. The Crafthall lies back to the west.
EndText
    );
    set("item_desc", ([
        "bottles" : "Some glow green, some glow gold, and one glows a color you don't have a word for.\n",
        "drawers" : "Labeled in a dozen scripts. One simply reads: Probably Fine.\n",
        "sticks" : "They lean ever so slightly toward you. It's flattering, in a strange way.\n",
        "counter" : "Dark wood, well polished, with a small brass bell resting on top.\n",
        "bell" : "A small brass bell. A note beside it reads: Back soon. Truly.\n",
    ]));
    set("exits", ([
        "west" : "/d/Nexus/rooms/crafthall",
    ]));
}
