// /d/FinalFrontier/npc/crusher.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("crusher");
    set("short", "Doctor Beverly Crusher");
    set("long", @EndText
    The chief medical officer, red-haired and brisk, making notes on a
padd without looking at it. She looks up at you with a doctor's glance,
which takes in rather more than you might like.
EndText
    );
    set("id", ({ "crusher", "doctor", "beverly", "doctor crusher" }));
    set("gender", "female");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N makes a note on a padd without looking at it." }),
        ({ "say", "says", "Sit down. You look like you haven't slept." }),
    }));
    set_inquiry(([
        "journal" : "Background reading. Somebody on this ship had a bad few years. I like to keep up.",
        "neural" : "Background reading. Somebody on this ship had a bad few years. I like to keep up.",
        "sleep" : "Nobody on this ship sleeps enough. I have stopped saying so.",
    ]), "Ask me something medical.");
}
