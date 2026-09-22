// /d/FinalFrontier/npc/laforge.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("laforge");
    set("short", "Lieutenant Commander Geordi La Forge");
    set("long", @EndText
    The chief engineer, with a VISOR across his eyes and a padd in each
hand, frowning at one of them. He has the easy, distracted warmth of
somebody who likes you fine but is currently thinking about a plasma
conduit.
EndText
    );
    set("id", ({ "laforge", "la forge", "geordi", "engineer", "chief engineer" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N frowns at a display, then at the core, then at the display again." }),
        ({ "say", "says", "She's running fine. She's always running fine. That's what worries me." }),
        ({ "emote", "$N taps the fault log and does not close anything." }),
    }));
    set_inquiry(([
        "core" : "Steady as she goes. You could set a clock by her. Some people have.",
        "conduit" : "Closed it four times. Still open. Leave it with me.",
        "deck 11" : "Closed it four times. Still open. Leave it with me.",
        "visor" : "Sees everything. Including things I would rather not.",
    ]), "Not my department. Try the bridge.");
}
