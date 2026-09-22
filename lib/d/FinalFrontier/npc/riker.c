// /d/FinalFrontier/npc/riker.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("riker");
    set("short", "Commander William Riker");
    set("long", @EndText
    Broad, bearded, and entirely at ease, with the posture of a man who
has made himself comfortable in every chair on this ship at one time or
another. He has the look of somebody about to tell you a story you will
not entirely believe.
EndText
    );
    set("id", ({ "riker", "commander", "will", "number one" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N steps over the back of a chair to sit down, as though chairs were an obstacle to be overcome." }),
        ({ "emote", "$N leans on the tactical rail and says nothing, grinning slightly." }),
        ({ "say", "says", "Poker tonight. You're welcome. Bring money you can afford to lose." }),
    }));
    set_inquiry(([
        "poker" : "Deck ten, most nights. Data plays. I would think carefully before you do.",
        "trombone" : "Badly, according to everyone. I disagree.",
        "captain" : "Ready room. Knock first. He will say come in regardless.",
    ]), "Couldn't tell you.");
    set_range(60, ({
        "/d/FinalFrontier/deck01/bridge",
        "/d/FinalFrontier/deck01/aft_passage",
        "/d/FinalFrontier/deck01/observation_lounge",
    }));

}
