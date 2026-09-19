// /d/Avakuma/guild/hallway_1.c
// Shares its short with hallway_2; they are distinct rooms.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A hallway");
    set("long", @EndText
    A hallway east of the Grand Entrance Hall. Not so grand as the
entranceway, but the ceiling is vaulted all the same and marble columns
carry it. The north and south walls have tapestries hanging near their
respective doorways.
EndText
    );
    set("item_desc", ([
        "ceiling" : @EndText
    Vaulted in the manner of the Grand Entrance Hall, though neither so
high nor so grandiose.
EndText
        ,
        "columns" : @EndText
    Tall and cylindrical, standing off to either side and holding up the
vault. Polished to a bright sheen.
EndText
        ,
        "walls" : @EndText
    Quality granite blocks set in that same ivory-speckled mortar. North
and south they carry tapestries.
EndText
        ,
        "tapestries" : @EndText
    There are tapestries on both the north and south walls. To make out
what either depicts you would have to look at the wall it hangs on.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/guild/hallway_2",
        "north" : "/d/Avakuma/guild/guild_shop",
        "west"  : "/d/Avakuma/guild/entrance_hall",
        "south" : "/d/Avakuma/guild/training_hall",
    ]));
    set("exit_order", ({ "east", "north", "west", "south" }));
}
