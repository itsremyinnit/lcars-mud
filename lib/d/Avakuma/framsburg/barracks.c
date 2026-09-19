// /d/Avakuma/framsburg/barracks.c
// The front door is shut and does not open by walking north. The sign
// says to bang on it, and banging brings the housekeeper to let you in.
// "read sign" carries the notice text.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "Entrance to the guard barracks");
    set("long", @EndText
    The guard barracks of Framsburg stand over you, built of stone and
kept in better repair than anything else in the town. The front door is
large and firmly shut, with a sign on the wall beside it. The path up to
the door has been worn down to bare ground. Dust hangs in the air, drifting
in off the street behind you.
EndText
    );
    set("item_desc", ([
        "sign" : @EndText
    A slab of wood hung on the wall beside the door. The inscriptions
were cut into it with a knife, by someone in no particular hurry.
EndText
        ,
        "inscriptions" : @EndText
    There are letters carved into the sign, but making sense of them
means reading it.
EndText
        ,
        "door" : @EndText
    Large, wooden, and firmly closed. It will not be opened by putting
a shoulder to it.
EndText
        ,
        "walls" : @EndText
    Stone, well maintained, and square at every corner. The building
cannot be very old, though it is hard to say these things with stone.
EndText
        ,
        "path" : @EndText
    Worn down to bare earth, running from the street up to the door.
This is the way the barracks is used.
EndText
        ,
        "dust" : @EndText
    It billows up off the street and hangs in the air, enough to catch
in the throat.
EndText
        ,
        "barracks" : @EndText
    Built after the worst of the raids, by the look of it. Nothing this
sound stood through what happened to the rest of Framsburg.
EndText
        ,
        "street" : @EndText
    Busy, for a dead town. People pass through the old ruins on business
of their own, and somewhere out of sight a horse shifts and stamps.
EndText
        ,
    ]));
    set("exits", ([
        "south" : "/d/Avakuma/framsburg/hospital",
    ]));
    set("exit_order", ({ "north", "south" }));
    add_sealed("north",
        "The door is shut. The sign suggests banging on it.\n");
}

void init() {
    add_action("do_read", "read");
    add_action("do_bang", "bang");
}

int do_read(string str) {
    if (str != "sign" && str != "inscriptions") {
        notify_fail("Read what?\n");
        return 0;
    }
    write(
"    The sign on the wall reads: \"Welcome to the Framsburg barracks.  No\n"
"visitors unless on an official errand.  If you wish to enter, bang on the\n"
"door and an employee will help you.\"\n");
    return 1;
}

int do_bang(string str) {
    object dest;

    if (!str || (str != "door" && str != "on door")) {
        notify_fail("Bang on what?\n");
        return 0;
    }
    dest = find_object_or_load("/d/Avakuma/barracks/main_hall");
    if (!dest) {
        write("You bang on the door. Nothing answers.\n");
        return 1;
    }
    write(
"    As you bang on the huge door, you hear footsteps on the other side.\n"
"The door swings open and a small lady leads you in.\n");
    this_player()->move_player(dest, "$N is let in through the barracks door.\n");
    return 1;
}
