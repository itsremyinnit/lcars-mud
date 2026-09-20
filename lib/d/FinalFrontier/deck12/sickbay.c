// /d/FinalFrontier/deck12/sickbay.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Sickbay");
    set("long", @EndText
    White, bright, and cold by about two degrees. Six biobeds along the
inner wall, all of them empty and all of them made. The overhead sensor
clusters hang at rest. A surgical bay is partitioned off to starboard
behind a screen that is not currently drawn. Cabinets line the far wall,
sealed, labelled, and in alphabetical order. It is the tidiest room you
have been in aboard this ship, and the quietest, and it manages to be
both of those in a way that is not restful.
EndText
    );
    set("item_desc", ([
        "biobeds" : @EndText
    Six, in a row, empty. Each has a display above it showing a flat
green baseline for a patient who is not there.
EndText
        ,
        "clusters" : @EndText
    Sensor arrays on articulated arms, folded up out of the way above
each bed. They move on their own when there is a reason to.
EndText
        ,
        "cabinets" : @EndText
    Sealed, labelled, alphabetical, and locked. The labels are in a hand
so neat it is almost a typeface.
EndText
        ,
        "screen" : @EndText
    A partition around the surgical bay, currently pushed back. It runs
on a track in the ceiling and does not make a sound.
EndText
        ,
        "bay" : @EndText
    The surgical bay, sterile field off, instruments racked. Everything
in it is exactly parallel to everything else.
EndText
        ,
        "office" : @EndText
    A small office off the far end, door open, light on. There is a
chair, a desk and a medical journal open to an article about long-term
neural recovery. Somebody has been reading it carefully.
EndText
        ,
        "journal" : @EndText
    Open to an article on neural recovery following prolonged invasive
interface. The margins have notes in them. Several passages are
underlined twice.
EndText
        ,
    ]));
    set("exits", ([
        "aft" : "/d/FinalFrontier/deck12/turbolift",
    ]));
    set("exit_order", ({ "aft" }));
}
