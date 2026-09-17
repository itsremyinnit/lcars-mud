// /d/Nexus/rooms/hall_of_records.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Hall of Records");
    set("long", @EndText
Shelves of dark wood climb the walls here until they vanish into the
golden haze, and ladders on silent rails stand ready to reach them. Every
shelf holds books, scrolls, and bound folios, and in the stillness you can
almost hear the patient sound of a story waiting to be read. A great
lectern of carved stone stands in the center, bearing a single open book
whose pages are still blank. The Commons lies to the east.
EndText
    );
    set("item_desc", ([
        "shelves" : "They hold the record of every reality the Nexus touches. Most are still empty.\n",
        "ladders" : "They glide along their rails without a sound, as if they know where you want to go.\n",
        "lectern" : "Carved stone, cool to the touch, with an open book resting upon it.\n",
        "book" : "The pages are blank, yet they have the feel of a chronicle about to begin.\n",
    ]));
    set("exits", ([
        "east" : "/d/Nexus/rooms/commons",
    ]));
}
