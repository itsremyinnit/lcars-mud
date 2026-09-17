// /d/Nexus/rooms/kindled_hearth.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Kindled Hearth");
    set("long", @EndText
A fire burns in a hearth of hewn grey stone, old as the Nexus and warm as
a kitchen. Around it, mismatched chairs have settled in like regulars who
never quite went home, and mugs hang from pegs along the mantel, no two
alike. A long table bears the scars of a thousand good evenings. A worn
stair climbs toward the quiet rooms above, and the Grand Concourse lies
back to the west.
EndText
    );
    set("item_desc", ([
        "fire" : "It crackles contentedly, and never seems to need more wood.\n",
        "hearth" : "Big enough to walk into, though the fire suggests you don't.\n",
        "chairs" : "No two match. Every one of them looks like the most comfortable chair here.\n",
        "mugs" : "Pewter, clay, horn, and one that is definitely a small helmet.\n",
        "stair" : "Worn stone steps, dipped in the middle from long use, climbing upward.\n",
    ]));
    set("exits", ([
        "west" : "/d/Nexus/rooms/grand_concourse",
        "up"   : "/d/Nexus/rooms/inn",
    ]));
    call_other("/d/Nexus/boards/hearth_board", "???");
}
