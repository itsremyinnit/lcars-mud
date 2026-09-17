// /d/Nexus/rooms/inn.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Inn");
    set("long", @EndText
The stair opens onto a quiet landing, lit by lamps turned low. A thick
runner of green wool muffles every step, and the air smells of cedar and
clean linen. Corridors lead off to either side, where the rooms of those
who dwell in the Nexus will one day line the walls. For now, the doors are
still being dreamed. The stair leads back down to the Hearth.
EndText
    );
    set("item_desc", ([
        "runner" : "Green wool, soft and deep. It makes you want to take your boots off.\n",
        "corridors" : "They stretch away east and west, peaceful and not yet finished.\n",
        "lamps" : "Turned low, as if someone were already asleep.\n",
    ]));
    set("exits", ([
        "down" : "/d/Nexus/rooms/kindled_hearth",
    ]));
}
