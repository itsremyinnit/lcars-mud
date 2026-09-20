// /d/FinalFrontier/deck01/bridge.c
// Exit convention for the domain: cardinals where you are navigating,
// named exits where the destination is its own place, "out" where there
// is one way back. Port and starboard stay in the prose and out of the
// exits, which is where the vocabulary belongs.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Main Bridge");
    set("long", @EndText
    The bridge is smaller than you expected and quieter than you hoped. A
horseshoe of consoles wraps the upper deck behind you, and below, three
seats face a viewscreen showing stars that do not appear to be moving at
all. The carpet is grey and immaculate and worn pale in a track between
the turbolift and the command chair. Somebody has been walking that line
for seven years. The ready room lies off the starboard corner, a short
passage to the observation lounge off the port one, and the turbolift
stands aft to starboard with its indicator lit.
EndText
    );
    set("item_desc", ([
        "viewscreen" : @EndText
    A wall of stars, steady and unhurried. At this magnification nothing
appears to move, which is a trick of scale rather than a fact about the
ship.
EndText
        ,
        "consoles" : @EndText
    Tactical, operations, engineering, science, environment. Most stand
unattended at this hour, running their own quiet arithmetic and waiting
for somebody to disagree with it.
EndText
        ,
        "carpet" : @EndText
    Grey, and spotless everywhere except the worn track between the
turbolift and the command chair. Seven years of one man thinking on his
feet.
EndText
        ,
        "chair" : @EndText
    The command chair, with its arm panel dimmed to standby. Somebody has
left a cup on the console beside it, gone cold.
EndText
        ,
        "cup" : @EndText
    Earl Grey, cold, half finished. The replicator pattern for it is
apparently the most-used on the ship by a considerable margin.
EndText
        ,
        "seats" : @EndText
    Conn, ops, and the command chair between and behind them. The forward
two are empty; their stations are locked to autopilot.
EndText
        ,
        "stars" : @EndText
    Unfamiliar ones. You could not name a single constellation from here,
which is either the point of the place or the price of it.
EndText
        ,
    ]));
    set("exits", ([
        "northwest" : "/d/FinalFrontier/deck01/aft_passage",
        "northeast" : "/d/FinalFrontier/deck01/turbolift",
        "readyroom" : "/d/FinalFrontier/deck01/ready_room",
    ]));
    set("exit_order", ({ "northwest", "northeast", "readyroom" }));
}
