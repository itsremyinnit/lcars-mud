#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 6 Aft");
    set("long", @EndText
    The corridor ends here at a bulkhead that was clearly meant to be a
door into something and is currently just a bulkhead. Security is to
starboard, its entry marked and lit. There is a scanner arch set into the
deck at the security door which registers you as you approach and does
not comment.
EndText
    );
    set("item_desc", ([
        "bulkhead" : @EndText
    Plate, seamed, unfinished at the edges. Whatever was supposed to be
on the other side of this has not been built.
EndText
        ,
        "arch" : @EndText
    A scanner frame in the deck and doorway at the security entrance. It
reads you on the way past. Nothing happens, which is the intended result.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/FinalFrontier/deck06/corridor_mid",
        "west"  : "/d/FinalFrontier/deck06/brig_entry",
    ]));
    set("exit_order", ({ "north", "west" }));
}
