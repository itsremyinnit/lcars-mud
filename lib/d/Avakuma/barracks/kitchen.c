// /d/Avakuma/barracks/kitchen.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The barracks kitchen");
    set("long", @EndText
    A large table takes up the middle of the kitchen, and a fireplace
burns in the west corner. The stove stands along the east wall. Whatever
the smell is that has followed you through the barracks, this is where it
starts, and close to its source it is worse. Cookbooks lie piled on the
shelf in no order at all, thick with dust.
EndText
    );
    set("item_desc", ([
        "table" : @EndText
    Wood, in fair condition, with candles on it and utensils scattered
across it in no arrangement whatever.
EndText
        ,
        "fireplace" : @EndText
    Burning steadily and keeping the room warm. It is the only light in
here.
EndText
        ,
        "stove" : @EndText
    Filthy, and sizzling hot. Keep your hands off it unless you want to
add to the smell.
EndText
        ,
        "smell" : @EndText
    Burned meat, and this is where it is made. Standing here does not
help identify it.
EndText
        ,
        "books" : @EndText
    Cookbooks, every one, and full of good recipes going entirely to
waste in this room.
EndText
        ,
        "bookshelf" : @EndText
    Against the east wall, under a coat of dust, with the books shoved
in anyhow.
EndText
        ,
        "dust" : @EndText
    Thick on everything. The housekeeper is evidently not permitted in
here, which seems a poor arrangement for all concerned.
EndText
        ,
        "utensils" : @EndText
    Scattered across the table, and not one of them clean.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/barracks/messhall",
    ]));
    set("exit_order", ({ "north" }));

    set("objects", ([
        "/d/Avakuma/barracks/npc/chef" : 1,
    ]));
    spawn_objects();
}
