// /d/FinalFrontier/deck10/corridor_ten.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Corridor, Deck 10 Forward");
    set("long", @EndText
    A corridor that curves gently to both sides, so you can never see
more than thirty feet of it at once. The walls are a soft grey with a
band of light running along at shoulder height, and every dozen paces a
wall panel shows a schematic of this deck with a cheerful little dot on
it indicating you. Ten-Forward is forward. The turbolift is aft.
EndText
    );
    set("item_desc", ([
        "panel" : @EndText
    A wall display showing this deck in cutaway, with a dot marking where
you are standing. The dot is slightly ahead of where you actually are,
which is either a calibration issue or an opinion.
EndText
        ,
        "band" : @EndText
    A strip of light at shoulder height running the length of the
corridor. It is the only thing in here that does not curve.
EndText
        ,
        "walls" : @EndText
    Soft grey, seamless, and curved. There is not a corner anywhere on
this deck that you can find by looking.
EndText
        ,
    ]));
    set("exits", ([
        "forward" : "/d/FinalFrontier/deck10/ten_forward",
        "aft"     : "/d/FinalFrontier/deck10/turbolift",
    ]));
    set("exit_order", ({ "forward", "aft" }));

    set("objects", ([
        "/d/FinalFrontier/npc/crewman" : 1,
    ]));
    spawn_objects();
}
