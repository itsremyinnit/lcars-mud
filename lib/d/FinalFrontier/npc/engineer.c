// /d/FinalFrontier/npc/engineer.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("engineer");
    set("short", "An engineer");
    set("long", @EndText
    Gold-shouldered, sleeves pushed up, bent over a console and muttering
at a graph that is not doing what it was told.
EndText
    );
    set("id", ({ "engineer", "crewman", "crew" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N mutters at a graph." }),
        ({ "emote", "$N runs the same diagnostic again." }),
    }));
}
