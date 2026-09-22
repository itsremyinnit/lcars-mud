// /d/FinalFrontier/npc/guinan.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("guinan");
    set("short", "Guinan");
    set("long", @EndText
    Small, unhurried, in a broad hat and robes, polishing a glass behind
the bar. She has the look of somebody who has seen a very great deal and
found most of it interesting, and she looks at you as if you might be.
EndText
    );
    set("id", ({ "guinan", "bartender", "hostess" }));
    set("gender", "female");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N polishes a glass that did not need it." }),
        ({ "say", "says", "Sit. You look like you have something on your mind. Most people who come in here at this hour do." }),
    }));
    set_inquiry(([
        "drink" : "Something that isn't on the menu. Trust me.",
        "q" : "Don't get me started.",
        "bottles" : "Real ones. The replicator makes a fine drink. It doesn't make a story.",
    ]), "Some things you have to find out for yourself.");
}
