// /d/Avakuma/framsburg/leaders_house.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "Half of a ruined house");
    set("long", @EndText
    Half this house is simply gone. The whole eastern side came down to
the weather, and what is left stands square and shows no sign of
following it. The roof slopes up from the remaining walls to make a
canopy over a table.
EndText
    );
    set("item_desc", ([
        "roof" : @EndText
    It rises from the walls still standing to a point some fifteen feet
off the ground.
EndText
        ,
        "canopy" : @EndText
    Roof and walls together make a decent covering over the table.
EndText
        ,
        "table" : @EndText
    Not a large one. Large enough for the work done across it.
EndText
        ,
        "walls" : @EndText
    The west wall is whole. Half of the north and south still stand.
The east is gone entirely.
EndText
        ,
        "house" : @EndText
    Half a house, and the better half. What is left of it is sounder
than most of the whole ones in Framsburg.
EndText
        ,
    ]));
    set("exits", ([
        "east" : "/d/Avakuma/framsburg/kitchen",
    ]));
    set("exit_order", ({ "east" }));
}
