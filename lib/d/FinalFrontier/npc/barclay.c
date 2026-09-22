// /d/FinalFrontier/npc/barclay.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("barclay");
    set("short", "Lieutenant Reginald Barclay");
    set("long", @EndText
    Tall, thin, and slightly hunched, as though the ship were a size too
small for him. He fidgets with a spanner he does not seem to know he is
holding, and he keeps not looking at the holodeck door in a way that is
somehow very noticeable.
EndText
    );
    set("id", ({ "barclay", "reginald", "reg", "lieutenant" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N glances at the holodeck door and then very pointedly away from it." }),
        ({ "say", "stammers", "I-I was just, uh, checking the conduit. Routine." }),
        ({ "emote", "$N turns the spanner over in his hands, looks at it, and puts it in a pocket." }),
    }));
    set_inquiry(([
        "holodeck" : "It's, um. It's just a program. Everybody has programs.",
        "program" : "It's, um. It's just a program. Everybody has programs.",
        "conduit" : "Nobody believes me about the conduit.",
        "kitchen" : "I don't know anything about a kitchen.",
        "spanner" : "Oh! Is that where that went.",
    ]), "Oh! I, uh. I don't really know about that.");
    set_range(55, ({
        "/d/FinalFrontier/deck11/corridor",
        "/d/FinalFrontier/deck11/arboretum",
    }));

}
