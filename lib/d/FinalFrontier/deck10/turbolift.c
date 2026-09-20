// /d/FinalFrontier/deck10/turbolift.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([
        "out" : "/d/FinalFrontier/deck10/corridor_ten",
    ]));
    set("exit_order", ({ "out" }));
}
