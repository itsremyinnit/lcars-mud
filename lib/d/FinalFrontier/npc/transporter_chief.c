// /d/FinalFrontier/npc/transporter_chief.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("chief");
    set("short", "The transporter chief");
    set("long", @EndText
    A broad, sandy-haired chief with a working man's hands, standing at
the console with his back to the door. He has, somewhat unexpectedly, a
neat goatee. Everybody who meets him has the same thought, and he can see
you having it.
EndText
    );
    set("id", ({ "chief", "transporter chief", "operator" }));
    set("gender", "male");
    set("mass", 7000);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N rubs his chin, catches himself doing it, and stops." }),
        ({ "say", "mutters", "It's a goatee. People have goatees." }),
    }));
    set_inquiry(([
        "goatee" : "It's a GOATEE. It is not a statement. I am not from anywhere else.",
        "obrien" : "No relation. Different face. Look, it's the goatee, isn't it.",
        "o'brien" : "No relation. Different face. Look, it's the goatee, isn't it.",
        "transport" : "Where to? Somewhere on this ship, anyway. I'm not beaming you off it.",
    ]), "Just point at a pad.");
}
