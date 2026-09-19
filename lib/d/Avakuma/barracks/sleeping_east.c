// /d/Avakuma/barracks/sleeping_east.c
// The messhall's sleeping quarters. Identical text to sleeping_west in
// the original; the barracks map calls them east and west.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The guards sleeping quarters");
    set("long", @EndText
    A large table stands in the middle of the room, put there to make
cleaning armour and weapons less of a chore. Cabinets and closets line
the walls, bunks run along the east and north, and racks of various
kinds are mounted on the west. The whole room is clean and squared away.
Whoever sleeps here takes care of it.
EndText
    );
    set("item_desc", ([
        "table" : @EndText
    Large, and empty at the moment. Tools hang on hooks around it: rags,
hammers, cleaning oils.
EndText
        ,
        "cabinets" : @EndText
    Wooden, ranged along the walls, holding clothes and whatever else a
guard wants kept somewhere.
EndText
        ,
        "closets" : @EndText
    Wooden, ranged along the walls, holding clothes and whatever else a
guard wants kept somewhere.
EndText
        ,
        "bunks" : @EndText
    Fairly new bunkbeds, and made up tight enough to say something about
the discipline here. The men take pride in it.
EndText
        ,
        "racks" : @EndText
    Wooden, built to hold weapons while their owners sleep. Empty just
now, their holders all being out on duty.
EndText
        ,
    ]));
    set("exits", ([
        "south" : "/d/Avakuma/barracks/messhall",
    ]));
    set("exit_order", ({ "south" }));
}
