// /d/FinalFrontier/npc/data.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("data");
    set("short", "Lieutenant Commander Data");
    set("long", @EndText
    Pale gold skin, yellow eyes, and a stillness nobody else aboard quite
manages. His hands move over the ops console faster than the eye wants to
follow, and then stop completely, and he turns his head to look at you
with open and entirely sincere interest.
EndText
    );
    set("id", ({ "data", "commander data", "android" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N tilts his head a fraction, considers something, and resumes." }),
        ({ "emote", "$N's fingers move across the console faster than you can follow." }),
        ({ "say", "says", "I have been considering whether a joke told at 0300 is funnier. It does not appear to be." }),
    }));
    set_inquiry(([
        "spot" : "She is on deck eight, I believe. She is not lost. She is returning.",
        "cat" : "She is on deck eight, I believe. She is not lost. She is returning.",
        "humor" : "I am making progress. Commander Riker assures me otherwise.",
        "humour" : "I am making progress. Commander Riker assures me otherwise.",
    ]), "I do not have sufficient information to answer that.");
}
