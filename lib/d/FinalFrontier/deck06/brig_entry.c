// /d/FinalFrontier/deck06/brig_entry.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Security, Deck 6");
    set("long", @EndText
    The duty office for ship's security: a desk facing the door, a weapons
locker sealed into the inboard bulkhead, and a bank of monitors showing
corridors elsewhere on the ship in slow rotation. A second door aft leads
through to the detention cells. The desk is unoccupied at the moment but
the terminal on it is logged in, which suggests whoever sits here has not
gone far.
EndText
    );
    set("item_desc", ([
        "desk" : @EndText
    Facing the door, which is the only sensible way to arrange a desk in
a room like this. A half-finished report is open on the terminal.
EndText
        ,
        "locker" : @EndText
    Sealed into the bulkhead, biometric, with a small green indicator.
Its inventory is stencilled on the door: phasers, type one and type two,
and a count that has not changed in some time.
EndText
        ,
        "monitors" : @EndText
    A bank of them, cycling slowly through corridors on other decks.
Deck eleven comes up in the rotation, and the open access panel is
visible in the frame, and the work light, still on.
EndText
        ,
        "report" : @EndText
    Open on the terminal, half written: INCIDENT SUMMARY - UNAUTHORISED
ACCESS, DECK 11 PLASMA CONDUIT. The findings field is empty. The
recommendation field reads, in full: "Leave it."
EndText
        ,
        "terminal" : "    Logged in, screen active, with a report open on it.\n",
    ]));
    set("exits", ([
        "out"   : "/d/FinalFrontier/deck06/corridor_aft",
        "cells" : "/d/FinalFrontier/deck06/brig_cells",
    ]));
    set("exit_order", ({ "out", "cells" }));
}
