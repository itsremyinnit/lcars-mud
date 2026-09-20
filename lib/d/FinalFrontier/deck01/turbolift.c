// /d/FinalFrontier/deck01/turbolift.c
// The bridge's lift car. Inherits the shared turbolift behaviour and adds
// the way back onto the bridge.
#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([
        "out" : "/d/FinalFrontier/deck01/bridge",
    ]));
    set("exit_order", ({ "out" }));
}
