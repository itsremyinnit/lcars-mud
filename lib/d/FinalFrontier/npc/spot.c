// /d/FinalFrontier/npc/spot.c
#include "/d/FinalFrontier/frontier.h"
inherit FF_NPC;

void create() {
    ::create();
    set_name("spot");
    set("short", "Spot");
    set("long", @EndText
    Orange, short-haired, and entirely at ease, with the flat interest of
something that has decided you are not interesting. She wears a plain
collar with a small tag: SPOT, and beneath that, DECK 2, QUARTERS 2517,
and beneath that, in smaller lettering: SHE IS NOT LOST. SHE IS
RETURNING.
EndText
    );
    set("id", ({ "spot", "cat", "orange cat" }));
    set("gender", "female");
    set("mass", 7000);
    enable_commands();
    set_chat(4, ({
        ({ "emote", "$N sits down in the exact middle of the corridor." }),
        ({ "emote", "$N regards you, and then pointedly regards a spot on the wall instead." }),
        ({ "emote", "$N sets off down the corridor with the air of someone late for an appointment." }),
    }));
    set_range(45, ({
        "/d/FinalFrontier/deck08/corridor_fore",
        "/d/FinalFrontier/deck08/corridor_port",
        "/d/FinalFrontier/deck08/corridor_port_aft",
        "/d/FinalFrontier/deck08/corridor_starboard",
        "/d/FinalFrontier/deck08/corridor_aft",
    }));

}
