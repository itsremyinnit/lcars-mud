#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([ "out" : "/d/FinalFrontier/deck08/corridor_aft" ]));
    set("exit_order", ({ "out" }));
}
