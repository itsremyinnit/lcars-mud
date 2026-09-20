// /d/FinalFrontier/deck12/turbolift.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([
        "out" : "/d/FinalFrontier/deck12/sickbay",
    ]));
    set("exit_order", ({ "out" }));
}
