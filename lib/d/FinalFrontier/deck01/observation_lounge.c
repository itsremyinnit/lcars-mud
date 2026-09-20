// /d/FinalFrontier/deck01/observation_lounge.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "The Observation Lounge");
    set("long", @EndText
    A long table of dark wood under a long window, with a dozen chairs
pushed in at precise intervals by someone who cared about it. Models of
ships hang along the inner bulkhead in order of age, each smaller and
stranger than the last as they go back. The room has the particular
stillness of somewhere that hosts difficult conversations and is empty
between them. A padd lies on the table where somebody left it.
EndText
    );
    set("item_desc", ([
        "table" : @EndText
    Dark wood, real or a very committed replication, long enough to seat
a dozen with room to lean. There are faint rings at three of the places.
EndText
        ,
        "window" : @EndText
    It runs the length of the room and shows the nacelles from behind,
holding their steady blue. You can watch the ship think from here.
EndText
        ,
        "models" : @EndText
    Ships that carried this name before, in order, going back further
than seems reasonable. The oldest is a grey ocean-going thing with a
single stack, and the one after it does not appear to have a warp drive
at all.
EndText
        ,
        "chairs" : @EndText
    A dozen, pushed in at intervals so even it can only be deliberate.
One at the far end is fractionally out of line.
EndText
        ,
        "padd" : @EndText
    Left face-down on the table. Turning it over shows a duty roster with
three names circled and a note in the margin that reads only: ASK HIM.
EndText
        ,
    ]));
    set("exits", ([
        "forward" : "/d/FinalFrontier/deck01/bridge",
    ]));
    set("exit_order", ({ "forward" }));
}
