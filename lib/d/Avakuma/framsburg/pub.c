// /d/Avakuma/framsburg/pub.c
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined pub");
    set("long", @EndText
PLACEHOLDER. The ruined pub. Arrival point through the Towers Arch,
and the way into the Sheriff's Guild through the nailed board.
EndText
    );
    set("exits", ([
        "west" : "/d/Avakuma/framsburg/road_north",
    ]));
}
