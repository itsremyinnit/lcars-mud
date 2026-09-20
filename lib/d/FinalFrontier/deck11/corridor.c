// /d/FinalFrontier/deck11/corridor.c
// The deck every loose end has been pointing at. Public space, plain
// register, and the payoff is in what is physically here rather than in
// anybody explaining it.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 11");
    set("long", @EndText
    Quieter than the residential decks and colder by a degree or two.
Holodecks one and two face each other across the corridor, their arch
doors shut and their status panels dark. Further along, an access panel
in the inboard bulkhead has been removed and propped against the wall,
and the conduit behind it is exposed. Somebody has rigged a work light
that is still on. The arboretum is aft.
EndText
    );
    set("item_desc", ([
        "panel" : @EndText
    Lifted off its mounts and leaned against the bulkhead beside the
opening. The fasteners are in a neat line on the deck where somebody set
them down in order.
EndText
        ,
        "conduit" : @EndText
    A plasma conduit, port side, running fore and aft behind the wall.
The insulation has been opened along a two-foot section and left open.
There is a scorch mark on the inside of the housing, faint, and old, and
nobody has cleaned it off because nobody has closed this up.
EndText
        ,
        "scorch" : @EndText
    A phase burn, a hand's breadth across, on the inner face of the
housing. It is not fresh. Under it, scratched into the metal with
something small and sharp, are four tally marks.
EndText
        ,
        "marks" : @EndText
    Four tally marks scratched into the housing beside the burn. They are
the same size and the same depth and they were not made at the same time.
EndText
        ,
        "light" : @EndText
    A portable work light clamped to the open edge of the panel, still
burning, aimed into the conduit. Its charge indicator says it has been on
for nineteen days.
EndText
        ,
        "holodecks" : @EndText
    One and two, facing each other. Both arch doors shut. Holodeck one's
status panel is dark; holodeck two's shows a single amber line reading
PROGRAM SUSPENDED, no title given.
EndText
        ,
        "spanner" : @EndText
    A spanner, on the deck, half under the lip of the opening. It matches
the empty slot in the toolkit two decks up.
EndText
        ,
    ]));
    set("exits", ([
        "holodeck" : "/d/FinalFrontier/deck11/holodeck_two",
        "aft"      : "/d/FinalFrontier/deck11/arboretum",
        "lift"     : "/d/FinalFrontier/deck11/turbolift",
    ]));
    set("exit_order", ({ "holodeck", "aft", "lift" }));
}
