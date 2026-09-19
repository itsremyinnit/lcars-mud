// /d/Avakuma/orc/end_of_road.c
// INFERRED: southwest -> filthy_road_north. West is confirmed.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set_outdoors();
    set("short", "The end of the road");
    set("long", @EndText
    The smell at this end of town is worse than anywhere behind you, and
every instinct worth having says to go back southwest and go quickly. A
few houses stand nearby.
EndText
    );
    set("item_desc", ([
        "houses" : @EndText
    The one west has a good-looking roof on it. The one south is
surprisingly clean, which in this place is the more troubling of the two.
EndText
        ,
        "smell" : @EndText
    Worse here than anywhere behind you, and getting worse the longer
you stand in it.
EndText
        ,
        "instincts" : @EndText
    They are telling you to leave. They are not wrong.
EndText
        ,
    ]));
    set("exits", ([
        "southwest" : "/d/Avakuma/orc/filthy_road_north",
        "west"      : "/d/Avakuma/orc/dirty_house",
    ]));
    set("exit_order", ({ "southwest", "west" }));
}
