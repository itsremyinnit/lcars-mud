// /d/FinalFrontier/deck06/cargo_control.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Cargo Control");
    set("long", @EndText
    A small office overlooking the bay through a window that runs the
length of the inboard wall. A console, two chairs, and a wall of manifest
displays showing what is aboard, where it came from and where it is meant
to go. Most of the entries are routine. The room smells faintly of the
bay: dust, cold metal, and packing material.
EndText
    );
    set("item_desc", ([
        "window" : @EndText
    Down into the bay, the whole length of the wall. From up here the
grid on the deck makes sense as a system rather than as paint.
EndText
        ,
        "manifests" : @EndText
    Cargo listings by container: agricultural samples, replicator stock,
medical supplies, and one line flagged for attention reading only
PERSONAL EFFECTS - HOLD PENDING INSTRUCTION, with no name against it and
a date eleven months old.
EndText
        ,
        "console" : @EndText
    Bay controls, door lockouts, the freight transporter. All of it
duplicated on the bridge and in engineering, which is why nobody sits
here.
EndText
        ,
        "chairs" : "    Two, neither of them pushed in.\n",
    ]));
    set("exits", ([
        "aft"   : "/d/FinalFrontier/deck06/cargo_bay",
        "north" : "/d/FinalFrontier/deck06/corridor_port_aft",
    ]));
    set("exit_order", ({ "aft", "north" }));
}
