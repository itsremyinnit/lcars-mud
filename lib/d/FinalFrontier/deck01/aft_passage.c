// /d/FinalFrontier/deck01/aft_passage.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Aft Passage, Deck 1");
    set("long", @EndText
    A short length of corridor connecting the bridge to the observation
lounge, barely long enough to count as a room. There is a replicator set
into the port bulkhead and a bench opposite it that nobody has ever been
seen sitting on. The deck plate here has been lifted and reseated at some
point; you can see the seam.
EndText
    );
    set("item_desc", ([
        "replicator" : @EndText
    Set into the bulkhead at chest height. Its usage log is visible if
you care to look, and it is almost entirely tea.
EndText
        ,
        "bench" : @EndText
    Grey, moulded, bolted down, and to all appearances never used. It is
possible it was installed by someone who had opinions about corridors.
EndText
        ,
        "seam" : @EndText
    The deck plate has been lifted and put back. Whatever needed getting
at, somebody got at it in a hurry and did not quite line it up again.
EndText
        ,
        "log" : @EndText
    Tea, Earl Grey, hot. Several thousand times. Then, once, three weeks
ago, hot chocolate with cinnamon, at 0340.
EndText
        ,
    ]));
    set("exits", ([
        "southeast" : "/d/FinalFrontier/deck01/bridge",
        "lounge"    : "/d/FinalFrontier/deck01/observation_lounge",
    ]));
    set("exit_order", ({ "southeast", "lounge" }));
}
