// /d/FinalFrontier/deck36/engineering.c
// Public space: plain register. It is a machine room and the people in it
// talk about it like a machine.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Main Engineering");
    set("long", @EndText
    Two decks of open space built around the warp core, which runs from
the floor to well above the upper gallery and pulses blue at a rate that
has nothing to do with anything you can see. The noise is constant and
lower than you expected, more felt than heard. Consoles ring the room at
both levels. The master systems display covers most of the aft bulkhead,
showing the ship in cutaway with roughly four hundred things happening at
once. Somebody's jacket is over the back of a chair. There is a fault log
mounted beside the core.
EndText
    );
    set("item_desc", ([
        "core" : @EndText
    A column of blue light in a clear housing, running floor to ceiling
and through both galleries. It pulses. Standing close, you can feel it in
your teeth rather than hear it.
EndText
        ,
        "display" : @EndText
    The master systems display: the whole ship in cutaway, every deck,
every system, colour-coded and updating. Three small amber marks on deck
eleven. Everything else is green.
EndText
        ,
        "consoles" : @EndText
    A ring of them at each level, most showing throughput graphs that
have been flat for weeks. Two are running a diagnostic that appears to be
in its fourth hour.
EndText
        ,
        "jacket" : @EndText
    Uniform jacket, gold shoulders, over the back of a chair. It has been
there long enough that nobody is going to mention it.
EndText
        ,
        "gallery" : @EndText
    The upper level, a walkway ringing the core. From up there you would
be looking down into it, which some people can do and some cannot.
EndText
        ,
        "log" : @EndText
    A padd on a bracket beside the core, for faults that are not urgent
enough to wake anybody. The top entry has been made four times:

  INTERMITTENT PHASE VARIANCE, PORT PLASMA CONDUIT, DECK 11.
  Closed: no fault found.
  Closed: no fault found.
  Closed: no fault found.
  Reopened 0340 three weeks ago. Still open.
EndText
        ,
        "marks" : @EndText
    Three amber marks on deck eleven, clustered close together. Nothing
flashing, nothing urgent. They have been amber for a while.
EndText
        ,
    ]));
    set("exits", ([
        "aft" : "/d/FinalFrontier/deck36/turbolift",
    ]));
    set("exit_order", ({ "aft" }));

    set("objects", ([
        "/d/FinalFrontier/npc/laforge" : 1,
        "/d/FinalFrontier/npc/engineer" : 2,
    ]));
    spawn_objects();
}
