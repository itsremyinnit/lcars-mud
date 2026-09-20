// /d/FinalFrontier/deck08/quarters_guest.c
// Personal space: loaded register.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Guest Quarters 0804");
    set("long", @EndText
    Made up for somebody and not yet slept in. The bed is turned down at
one corner. There is a desk, a chair, a viewport, and a small table by
the bed with a carafe of water on it and a glass turned upside down. On
the desk somebody has left a welcome padd and, beside it, a plant in a
clay pot that is not standard issue and has been watered recently.
EndText
    );
    set("item_desc", ([
        "bed" : @EndText
    Turned down at one corner, precisely, the way a hotel does it. The
ship evidently has opinions about hospitality.
EndText
        ,
        "padd" : @EndText
    A welcome brief: deck layout, meal hours, a note that Ten-Forward
keeps no hours at all, and at the bottom, added by hand rather than
generated: "If you are up at odd hours you will not be the only one."
EndText
        ,
        "plant" : @EndText
    Something broad-leaved in a clay pot, the soil dark with recent
water. There is no card. The pot has a chip out of the rim that has been
smoothed down rather than repaired.
EndText
        ,
        "carafe" : "    Water, and a glass turned upside down beside it. Both are clean.\n",
        "viewport" : @EndText
    Stars, and the curve of the hull falling away. From this angle you
can see the running lights go along the rim in sequence.
EndText
        ,
        "desk" : "    Bare except for the padd and the plant. The chair is pushed in square.\n",
    ]));
    set("exits", ([
        "out" : "/d/FinalFrontier/deck08/corridor_port",
    ]));
    set("exit_order", ({ "out" }));
}
