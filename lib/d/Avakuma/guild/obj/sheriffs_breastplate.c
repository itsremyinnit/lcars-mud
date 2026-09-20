// /d/Avakuma/guild/obj/sheriffs_breastplate.c
#include <mudlib.h>
inherit ARMOR;

void create() {
    set("id", ({ "breastplate", "sheriff's breastplate", "sheriffs breastplate", "plate" }));
    set("short", "a sheriff's breastplate");
    set("long", @EndText
    A solid plate of steel shaped to the chest, with the crest of the
Rim-Ainacam worked into it just below the collar. It is heavy, and it was
not made for running.
EndText
    );
    set("bulk", 140);
    set("mass", 2200);
    set("value", ({ 260, "gold" }));
    set("type", "suit");
    set("armor", 10);
}
