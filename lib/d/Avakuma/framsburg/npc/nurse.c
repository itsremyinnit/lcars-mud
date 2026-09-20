// /d/Avakuma/framsburg/npc/nurse.c
// A functional healer in the original: heals, and revives the dead.
// Those mechanics are deferred; the chat is not.
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("nurse");
    set("short", "A tired nurse");
    set("long", @EndText
    She is here to help the soldiers recover from some rather nasty
wounds, and she has been at it a long while. If you are civil about it
she can be asked for healing, or for reviving in cases of death.
EndText
    );
    set("id", ({ "nurse", "tired nurse", "woman" }));
    set("gender", "female");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 5000);
    set("bulk", 250);
    enable_commands();
    set_chat(5, ({
        ({ "say", "whispers", "Go back to sleep, you need your rest." }),
        ({ "say", "says",     "Will you keep still?" }),
    }));
    set_inquiry(([
        "healing"       : "Ask me nicely and I will see what I can do.",
        "heal"          : "Ask me nicely and I will see what I can do.",
        "soldiers"      : "They were lucky. Most of them. Some more than others.",
        "wounds"        : "Orc work. I have seen a great deal of it lately.",
        "orcs"          : "I have no opinion on orcs that is fit to say aloud.",
    ]), "I have my hands full, sorry.");

}
