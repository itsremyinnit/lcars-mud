// /d/Avakuma/guild/jail.c
// In the original you are thrown in here by the guild guard, shackled,
// and held until a Framsburg barracks guard releases you. None of that
// is built: the room exists, nothing leads here, and south simply works.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "Framsburg's jail");
    set("long", @EndText
PLACEHOLDER. Framsburg's jail. In the original you arrive here shackled
to an iron ball and wait out a sentence. Unreachable for now.
EndText
    );
    set("exits", ([
        "south" : "/d/Avakuma/guild/entrance_hall",
    ]));
    set("exit_order", ({ "south" }));
}
