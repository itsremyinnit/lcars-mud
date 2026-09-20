// /d/Avakuma/orc/filthy_house.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A filthy house");
    set("long", @EndText
    Most of the walls are standing here, though openings have been put
through them to the north and west by whoever wanted to come and go that
way. The roof is whole apart from the middle, which is gone. This is a
meeting place of some kind: there is a fire in the centre with a ring of
well-trodden dirt around it, and the whole room stinks.
EndText
    );
    set("item_desc", ([
        "walls" : @EndText
    Strong enough, though the exits were made by breaking straight
through them rather than asking anyone.
EndText
        ,
        "roof" : @EndText
    More a canopy over four walls than a roof, the middle being open.
The smoke has to go somewhere.
EndText
        ,
        "fire" : @EndText
    A large campfire in the middle of the room, flames standing about
three feet. Everything here is arranged around it. It burns far too hot
to put out, or to take a brand from.
EndText
        ,
        "dirt" : @EndText
    Compacted into a ring around the fire by a great many feet.
EndText
        ,
        "openings" : @EndText
    Gaping holes that allow travel where no door was ever intended.
EndText
        ,
        "house" : @EndText
    A house until somebody decided it would be a hall instead, and
altered it with whatever came to hand.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/orc/filthy_road_north",
        "west"  : "/d/Avakuma/orc/filthy_road_south",
    ]));
    set("exit_order", ({ "north", "west" }));

    set("objects", ([
        "/d/Avakuma/orc/npc/half_orc" : 1,
    ]));
    spawn_objects();
}
