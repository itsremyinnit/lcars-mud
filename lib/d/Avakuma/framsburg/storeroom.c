// /d/Avakuma/framsburg/storeroom.c
// Stock for the armoury wagon. Torches are stocked from /obj/torch, which
// already has light/extinguish and is worth nothing, so it cannot be
// handled, only bought.
#include <mudlib.h>
inherit "/std/shop/storeroom";

#define STOCK ({ \
    "/d/Avakuma/framsburg/obj/short_sword", \
    "/d/Avakuma/framsburg/obj/large_shield", \
    "/d/Avakuma/framsburg/obj/spear", \
    "/d/Avakuma/framsburg/obj/broadsword", \
    "/d/Avakuma/framsburg/obj/backpack", \
    "/obj/torch", \
})

void restock();

void create() {
    ::create();
    seteuid(getuid());
    restock();
}

void restock() {
    string *stock;
    object *inv;
    object ob;
    int i, j, have;

    stock = STOCK;
    inv = all_inventory(this_object());
    for (i = 0; i < sizeof(stock); i++) {
        have = 0;
        for (j = 0; j < sizeof(inv); j++)
            if (base_name(inv[j]) == stock[i]) have++;
        for (j = have; j < 2; j++) {
            ob = clone_object(stock[i]);
            if (ob) ob->move(this_object());
        }
    }
    call_out("restock", 600);
}
