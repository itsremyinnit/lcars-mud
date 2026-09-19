// /d/Avakuma/orc/chieftain.c
// The one sound building in the camp, which is the joke.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A house in nice shape");
    set("long", @EndText
    This house is in the best repair of anything you have seen since the
road, with its walls standing and a full roof over them. The smell is no
better here than in any of the others.
EndText
    );
    set("item_desc", ([
        "walls" : "    Good-looking, sturdy walls.\n",
        "roof" : @EndText
    A roof with no holes in it, which is a rare thing in these parts.
EndText
        ,
        "smell" : @EndText
    No better than anywhere else in the camp. Rank has its privileges,
and this is not one of them.
EndText
        ,
        "house" : @EndText
    Whole, maintained, and standing in the middle of a camp that is
neither. Somebody here is owed something.
EndText
        ,
    ]));
    set("exits", ([
        "east" : "/d/Avakuma/orc/dirty_house",
        "south" : "/d/Avakuma/orc/dirty_room",
    ]));
    set("exit_order", ({ "east", "south" }));
}
