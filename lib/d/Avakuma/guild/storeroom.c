// /d/Avakuma/guild/storeroom.c
// Stock for the guild shop. /std/shop.c sells whatever is in here.
#include <mudlib.h>
inherit "/std/shop/storeroom";

#define STOCK ({ \
    "/d/Avakuma/guild/obj/sheriffs_chain", \
    "/d/Avakuma/guild/obj/sheriffs_breastplate", \
    "/d/Avakuma/guild/obj/lochaber_axe", \
    "/d/Avakuma/guild/obj/backpack", \
})

void restock();

void create() {
    ::create();
    seteuid(getuid());
    restock();
}

// Keep two of each on the shelf. Called at load and on a timer, so the
// shop does not run dry after somebody buys the place out.
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
