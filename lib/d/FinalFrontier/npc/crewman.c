// /d/FinalFrontier/npc/crewman.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("crewman");
    set("short", "A crewman");
    set("long", @EndText
    A crewman in duty uniform, going somewhere with a padd, at the pace of
somebody who is not late yet.
EndText
    );
    set("id", ({ "crewman", "crew", "ensign" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N nods to you in passing." }),
    }));
    set_range(50, ({
        "/d/FinalFrontier/deck06/corridor_fore",
        "/d/FinalFrontier/deck06/corridor_mid",
        "/d/FinalFrontier/deck06/corridor_aft",
        "/d/FinalFrontier/deck06/corridor_port_aft",
        "/d/FinalFrontier/deck08/corridor_fore",
        "/d/FinalFrontier/deck08/corridor_port",
        "/d/FinalFrontier/deck08/corridor_port_aft",
        "/d/FinalFrontier/deck08/corridor_starboard",
        "/d/FinalFrontier/deck08/corridor_aft",
        "/d/FinalFrontier/deck10/corridor_ten",
        "/d/FinalFrontier/deck10/ten_forward",
    }));

}
