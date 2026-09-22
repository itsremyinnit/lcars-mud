// /d/FinalFrontier/npc/ogawa.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("ogawa");
    set("short", "Nurse Alyssa Ogawa");
    set("long", @EndText
    Quick and quiet, moving between the biobeds resetting displays nobody
is using. She gives you a small professional smile and goes on with it.
EndText
    );
    set("id", ({ "ogawa", "nurse", "alyssa" }));
    set("gender", "female");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N resets a biobed display and moves on to the next." }),
    }));
    set_inquiry(([
        "doctor" : "Office, or on her way to it.",
    ]), "The doctor would know.");
}
