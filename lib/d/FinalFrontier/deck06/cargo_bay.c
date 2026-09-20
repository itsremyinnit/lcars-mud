// /d/FinalFrontier/deck06/cargo_bay.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Cargo Bay Two");
    set("long", @EndText
    A space large enough to make you recalibrate how big the ship is. The
deck is marked out in a grid of yellow lines and tie-down points, and
containers are stacked along the port wall in a block three high with
numbers stencilled on their ends. The outboard wall is a cargo door, shut,
with a control pedestal beside it and a warning stripe painted on the deck
that you find you are standing well clear of without having decided to. A
transporter pad sits in the corner for freight nobody wants to carry.
EndText
    );
    set("item_desc", ([
        "containers" : @EndText
    Grey, standardised, stacked three high and numbered. Most are sealed.
One near the bottom of the stack has its seal broken and the lid resting
on rather than in place.
EndText
        ,
        "lid" : @EndText
    Resting on rather than seated. Inside: packing material, and a gap in
the packing material the size and shape of something that is no longer
there.
EndText
        ,
        "door" : @EndText
    The cargo door, shut and locked out, filling most of the outboard
wall. There is nothing on the other side of it but vacuum and a great
deal of distance.
EndText
        ,
        "pedestal" : @EndText
    The door control, keyed and currently locked out, with a physical
cover over the release that has to be lifted deliberately. Somebody
thought about this.
EndText
        ,
        "stripe" : @EndText
    Yellow and black, painted across the deck a good six feet inboard of
the cargo door. It is the sort of line that does not need explaining.
EndText
        ,
        "pad" : @EndText
    A freight transporter pad in the corner, wide and low, rated for mass
rather than for people. Its indicator is amber.
EndText
        ,
        "grid" : "    Yellow lines and recessed tie-downs, laid out across the whole deck.\n",
    ]));
    set("exits", ([
        "forward" : "/d/FinalFrontier/deck06/cargo_control",
    ]));
    set("exit_order", ({ "forward" }));
}
