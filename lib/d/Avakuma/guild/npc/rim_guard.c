// /d/Avakuma/guild/npc/rim_guard.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("guard");
    set("short", "A guild guard of the Rim-Ainacam");
    set("long", @EndText
    A large man standing guard over the entrance to the guild of the
Rim-Ainacam. His muscles move under his chain mail shirt. The hard
leather leggings he wears look as though they would turn the sharpest of
blades. The scabbard on his back is finely made and built for a
two-handed sword, and what you can see of the sword itself is of very
fine make. On the front of his red tunic, over the mail, is the
embroidered crest of the Rim-Ainacam.
EndText
    );
    set("id", ({ "guard", "guild guard", "rim-ainacam guard", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 10000);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
}
