// /d/FinalFrontier/deck01/ready_room.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "The Captain's Ready Room");
    set("long", @EndText
    A small room with a very large window. The desk is bare except for a
terminal turned away from the door and a single framed photograph facing
the chair. On a shelf behind it sits a book with actual paper in it, and
beside that a small aquarium, lit from above, containing one unhurried
fish. The room smells faintly of tea. Whoever works here does not appear
to have slept in it, though the couch under the window suggests the option
has been considered.
EndText
    );
    set("item_desc", ([
        "desk" : @EndText
    Bare, and deliberately so. A terminal turned away from the door, a
cup ring nobody has wiped, and nothing else.
EndText
        ,
        "window" : @EndText
    A tall curve of transparent aluminium, most of one wall. Stars, and
the long shallow arc of the saucer falling away below.
EndText
        ,
        "photograph" : @EndText
    A framed picture, turned to face the chair rather than the room: a
vineyard in hard sunlight, rows of vines going up a slope, and a
farmhouse with the shutters closed. Nobody is in it.
EndText
        ,
        "book" : @EndText
    Paper, bound in cloth, its spine cracked in several places from being
opened at the same passages. A ribbon marks a page near the end.
EndText
        ,
        "aquarium" : @EndText
    A small tank lit from above. A single lionfish moves through it
without appearing to notice you, or anything else.
EndText
        ,
        "fish" : @EndText
    A lionfish, all fins and warning colouration, entirely unbothered.
Its name is on a small plate at the base of the tank.
EndText
        ,
        "plate" : "    A small brass plate at the base of the tank. It reads: LIVINGSTON.\n",
        "couch" : @EndText
    Low and grey, under the window. It has the faintly compressed look of
furniture that gets used for thinking rather than sitting.
EndText
        ,
        "terminal" : @EndText
    Turned away from the door, screen dimmed. A report is open on it. You
can make out the header: PERSONNEL - PROMOTION RECOMMENDATIONS.
EndText
        ,
    ]));
    set("exits", ([
        "out" : "/d/FinalFrontier/deck01/bridge",
    ]));
    set("exit_order", ({ "out" }));
}
