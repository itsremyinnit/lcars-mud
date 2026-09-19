// /d/Avakuma/guild/outside.c
// The far side of the board passage. "push board" returns to the pub.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "Outside of an old, well-kept building");
    set("long", @EndText
PLACEHOLDER. Behind the pub wall, a building nobody has let fall down.
The way back is the board you came through.
EndText
    );
    set("exits", ([
        "east" : "/d/Avakuma/guild/entrance_hall",
    ]));
    set("exit_order", ({ "east" }));
}

void init() {
    add_action("push_board", "push");
}

int push_board(string str) {
    object dest;

    if (str != "board" && str != "boards") {
        notify_fail("Push what?\n");
        return 0;
    }
    dest = find_object_or_load(FRAMSBURG_PUB);
    if (!dest) {
        write("The board does not budge.\n");
        return 1;
    }
    write("You pop the loose board with your hand again and slip through.\n");
    this_player()->move_player(dest, "$N slips away through the wall.\n");
    return 1;
}
