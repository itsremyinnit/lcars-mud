// /d/Avakuma/barracks/lounge.c
// The office south is behind a real door, closed but not locked.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The barracks lounge");
    set("long", @EndText
    The lounge is a quiet room and means to stay that way. The walls are
wood and carry nothing at all. A middling table sits in the middle of the
floor with two chairs drawn up to either side of it, and on the table a
candle burned nearly to its base holds off the dark.
EndText
    );
    set("item_desc", ([
        "walls" : @EndText
    Wood, and bare of any artwork. Dull, and perfectly adequate for a
room off-duty men sit in.
EndText
        ,
        "table" : @EndText
    Wood, and little used. A few playing cards lie on it, and a candle
burned almost to nothing stands in the middle.
EndText
        ,
        "chairs" : @EndText
    Two wooden chairs to each side, fairly new, with patterns carved
into them.
EndText
        ,
        "candle" : @EndText
    Wax, and nearly gone. It is the only light in the room.
EndText
        ,
        "cards" : @EndText
    A few lying face down on the table, in the middle of a hand nobody
has come back to.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/barracks/main_hall",
        "north" : "/d/Avakuma/barracks/sleeping_west",
        "south" : "/d/Avakuma/barracks/office",
    ]));
    set("exit_order", ({ "east", "north", "south" }));
    create_door("south", "north", "A plain door", "closed");
}
