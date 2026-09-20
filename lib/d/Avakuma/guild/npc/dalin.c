// /d/Avakuma/guild/npc/dalin.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("dalin");
    set("short", "Dalin, the stoor bartender");
    set("long", @EndText
    Dalin, the stoor bartender, working the bar with a skill that only
comes from years of it.
EndText
    );
    set("id", ({ "dalin", "bartender", "stoor", "hobbit" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 5500);
    set("bulk", 250);
    enable_commands();
    set_chat(4, ({
        ({ "say", "says", "Why don't you try your luck at the darts? Three bulls-eyes and there's a prize in it." }),
        ({ "emote", "$N works the bar with the ease of a great many years at it." }),
    }));
    set_inquiry(([
        "darts"         : "Three bulls-eyes and there is a prize in it. Nobody has managed it lately.",
        "dart"          : "Three bulls-eyes and there is a prize in it. Nobody has managed it lately.",
        "prize"         : "Win it and find out.",
        "scoreboard"    : "Read it. Some of those numbers took years.",
        "beer"          : "Five, and worth it.",
        "guild"         : "I only keep the bar. The politics happen down the hall.",
    ]), "Could not tell you. Drink?");

}
