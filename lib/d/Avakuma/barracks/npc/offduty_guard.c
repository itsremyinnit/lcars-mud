// /d/Avakuma/barracks/npc/offduty_guard.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("guard");
    set("short", "An off-duty guard");
    set("long", @EndText
    A large guard with several bruises across his pale face, plain at a
glance. His eyes are green and look kind, though his brushy eyebrows
cover most of them. His hair is dark, almost black, going grey at the
sides. As you look at him he looks back, and the pleasantness goes out of
his face. You take a step back. He looks tough.
EndText
    );
    set("id", ({ "guard", "off-duty guard", "offduty guard", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9500);
    set("bulk", 250);
    enable_commands();
    set_chat(3, ({
        ({ "emote", "$N lays down a card without much interest in it." }),
    }));
}
