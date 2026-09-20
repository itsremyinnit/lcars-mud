// /d/FinalFrontier/deck36/turbolift.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([
        "out" : "/d/FinalFrontier/deck36/engineering",
    ]));
    set("exit_order", ({ "out" }));
}
