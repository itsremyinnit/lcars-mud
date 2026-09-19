// /d/Avakuma/guild/outside.c
// The far side of the board passage. "push board" returns to the pub.
// The barricades are deliberate camouflage, not decay.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "Outside of an old, well-kept building");
    set("long", @EndText
    The front of an old building on a long-abandoned street running
through Framsburg, and the building is in far better repair than the
street deserves. North and south the way has been barricaded with debris,
piled there to make this part of the town look derelict to the invading
forces of the Dark Lord. The edifice itself stands sturdy, with withering
ivy on its walls and a small set of steps leading inside. The ruined
house you came through is west.
EndText
    );
    set("item_desc", ([
        "building" : @EndText
    Well kept, and pointedly so. Somebody has maintained this while
letting everything around it go.
EndText
        ,
        "barricades" : @EndText
    Debris piled across the street north and south. It was put there to
be seen and dismissed.
EndText
        ,
        "debris" : @EndText
    Rubble and timber, arranged to look as though it fell that way.
EndText
        ,
        "ivy" : @EndText
    Withering on the walls, and left to wither. It helps the disguise.
EndText
        ,
        "steps" : @EndText
    A small set of steps up to the door, swept clean.
EndText
        ,
        "street" : @EndText
    Long abandoned, or meant to look it. Blocked at both ends.
EndText
        ,
    ]));
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
