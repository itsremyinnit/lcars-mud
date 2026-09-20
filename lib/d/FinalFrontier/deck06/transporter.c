#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Transporter Room Three");
    set("long", @EndText
    Six pads in a circle on a raised platform, and a console facing them
across the room where the operator stands with their back to the door.
The overhead emitters are recessed into the ceiling above each pad. The
room is very clean and very bright and there is nowhere in it to sit,
which is deliberate: nobody is meant to be in here long.
EndText
    );
    set("item_desc", ([
        "pads" : @EndText
    Six, circular, set flush into the platform, each with a ring of
indicator lights around it currently showing standby amber.
EndText
        ,
        "console" : @EndText
    Facing the platform. The sliders are worn smooth in the middle of
their travel and nowhere else.
EndText
        ,
        "emitters" : @EndText
    Recessed into the ceiling above each pad, aimed down. You would not
notice them if you were standing on a pad, which is also deliberate.
EndText
        ,
        "platform" : "    A low dais, two steps up, holding the pad circle.\n",
        "log" : @EndText
    The transport log, visible on the console: a list of site-to-site
transports with times. Nothing unusual, except that this room has logged
four transports to deck eleven in the last month, all of them one person,
all of them after 0300.
EndText
        ,
    ]));
    set("exits", ([
        "out" : "/d/FinalFrontier/deck06/corridor_fore",
    ]));
    set("exit_order", ({ "out" }));
}
