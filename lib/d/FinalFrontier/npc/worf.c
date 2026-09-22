// /d/FinalFrontier/npc/worf.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("worf");
    set("short", "Lieutenant Worf");
    set("long", @EndText
    A Klingon in a Starfleet uniform, the ridged brow set in an
expression that has not changed since you walked in. He regards you with
the particular stillness of a man deciding whether you are a threat, and
does not appear to have finished deciding.
EndText
    );
    set("id", ({ "worf", "lieutenant", "klingon" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N watches the door." }),
        ({ "emote", "$N reviews the monitors without appearing to move his eyes." }),
        ({ "say", "says", "I do not have a sense of humour. I have a sense of proportion." }),
    }));
    set_inquiry(([
        "brig" : "It is secure. It has always been secure.",
        "prune juice" : "A warrior's drink.",
        "report" : "The recommendation stands.",
        "deck 11" : "The recommendation stands.",
    ]), "That is not a matter for security.");
}
