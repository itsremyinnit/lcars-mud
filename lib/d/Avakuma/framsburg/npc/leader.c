// /d/Avakuma/framsburg/npc/leader.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("leader");
    set("short", "The men's leader");
    set("long", @EndText
    A noble looking man, tall and well built, with a bearing that leaves
no doubt why these people chose him to lead them.
EndText
    );
    set("id", ({ "leader", "mens leader", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9500);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
    set_inquiry(([
        "framsburg"     : "What is left of it is ours to hold. So we hold it.",
        "orcs"          : "They came down on us and we pushed them back as far as the battlefield. No further.",
        "men"           : "Good ones. Too few of them.",
        "barracks"      : "The guard keep it. It is the soundest building we have.",
        "battle"        : "We won it, if you want to call it that.",
    ]), "That is not for me to say.");

}
