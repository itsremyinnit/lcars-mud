// /d/Avakuma/guild/hallway_1.c
// Shares its short with hallway_2; they are distinct rooms.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A hallway");
    set("long", @EndText
PLACEHOLDER. The western hallway of the guild. The shop lies north,
the training hall south.
EndText
    );
    set("exits", ([
        "east"  : "/d/Avakuma/guild/hallway_2",
        "north" : "/d/Avakuma/guild/guild_shop",
        "west"  : "/d/Avakuma/guild/entrance_hall",
        "south" : "/d/Avakuma/guild/training_hall",
    ]));
    set("exit_order", ({ "east", "north", "west", "south" }));
}
