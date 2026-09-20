// /d/FinalFrontier/deck11/holodeck_two.c
// Personal space, in the sense that somebody made it personal. Loaded
// register. The suspended program is the answer to the 0340 thread, and
// it does not explain itself.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Holodeck Two");
    set("long", @EndText
    The program is suspended, which means the room is holding its last
frame and not running it. A kitchen, small, with a low ceiling and a
window over the sink showing a street in rain, stopped. There is a pot on
the stove, not steaming. Two chairs at a table, one pushed back. On the
table, two cups. The grid shows faintly through the far wall where the
program has been paused long enough for the edges to fray.
EndText
    );
    set("item_desc", ([
        "kitchen" : @EndText
    Somebody's, and a real one: the cupboard doors do not all match and
one of the handles has been replaced with a different handle. This was
built from memory, not from a catalogue.
EndText
        ,
        "window" : @EndText
    Rain on a street, stopped mid-fall. The drops hang. Beyond them a row
of houses with their lights on, and the whole image is very slightly too
warm, the way a remembered afternoon is.
EndText
        ,
        "pot" : @EndText
    On the stove, lid off, not steaming because nothing here is moving.
Hot chocolate. There is cinnamon in it.
EndText
        ,
        "cups" : @EndText
    Two, on the table, both used. One has been set down neatly. The other
has been put down in a hurry and left a ring.
EndText
        ,
        "chairs" : @EndText
    Two at the table. One is pushed in. The other has been pushed back
and left, at the angle a chair ends up at when somebody stands up
quickly.
EndText
        ,
        "table" : @EndText
    Scrubbed wood with a burn mark near one corner that the program has
reproduced faithfully, which means whoever built this remembered it.
EndText
        ,
        "grid" : @EndText
    The holodeck grid, showing faintly through the far wall. A program
left suspended this long starts to let the room underneath show at the
edges. Nobody has come back to either finish it or clear it.
EndText
        ,
        "wall" : "    The far wall, where the kitchen stops being a kitchen.\n",
    ]));
    set("exits", ([
        "out" : "/d/FinalFrontier/deck11/corridor",
    ]));
    set("exit_order", ({ "out" }));
}
