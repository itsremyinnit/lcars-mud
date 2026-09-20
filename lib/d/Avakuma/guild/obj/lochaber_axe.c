// /d/Avakuma/guild/obj/lochaber_axe.c
#include <mudlib.h>
inherit WEAPON;

void create() {
    set("id", ({ "axe", "lochaber", "lochaber axe" }));
    set("short", "a lochaber axe");
    set("long", @EndText
    This grim looking weapon has a long shaft with a thick
spike sticking up from the end of it. It is meant to keep the
opponent at a distance while causing grave wounds. With its 
long reach and heavy slashing capabilities, the lochaber axe 
is a vicious weapon to wield in battle.
EndText
    );
    set("bulk", 110);
    set("mass", 1400);
    set("value", ({ 144, "gold" }));
    set("weapon", 6);
    set("damage", ({ 6, 14 }));
    set("nosecond", 1);
    set("name", "axe");
    set_verbs(({ "swing at", "hook at", "hack at" }));
    set("type", "cutting");
}
