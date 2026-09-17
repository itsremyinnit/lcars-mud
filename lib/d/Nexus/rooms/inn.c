// /d/Nexus/rooms/inn.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

#define QUARTERS_D "/d/Nexus/adm/quarters_d"

void refresh_wings() {
    set("exits", ([ "down" : "/d/Nexus/rooms/kindled_hearth" ]));
    if (QUARTERS_D->owner_at("west", 1)) set("exits/west", "/d/Nexus/wings/west_1");
    if (QUARTERS_D->owner_at("east", 1)) set("exits/east", "/d/Nexus/wings/east_1");
}

void create() {
    ::create();
    set("short", "The Inn");
    set("long", @EndText
The stair opens onto a quiet landing, lit by lamps turned low. A thick
runner of green wool muffles every step, and the air smells of cedar and
clean linen. Corridors lead off to the east and west, lined with the doors
of those who dwell in the Nexus, each carved with its owner's rune. The
stair leads back down to the Hearth.
EndText
    );
    set("item_desc", ([
        "runner" : "Green wool, soft and deep. It makes you want to take your boots off.\n",
        "corridors" : "They stretch away east and west, each door marked with a different rune.\n",
        "lamps" : "Turned low, as if someone were already asleep.\n",
    ]));
    refresh_wings();
}
