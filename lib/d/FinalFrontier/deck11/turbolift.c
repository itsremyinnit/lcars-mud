#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([
        "out" : "/d/FinalFrontier/deck11/corridor",
    ]));
    set("exit_order", ({ "out" }));
}
