#include "/d/FinalFrontier/frontier.h"
inherit FF_TURBOLIFT;

void create() {
    ::create();
    set("exits", ([ "out" : "/d/FinalFrontier/deck06/corridor_fore" ]));
    set("exit_order", ({ "out" }));
}
