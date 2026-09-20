// /d/FinalFrontier/adm/d_master.c
// Must exist before [FinalFrontier] is ever added to /adm/etc/groups.
inherit "/adm/obj/master/d_master";

void create() {
    ::create();
    permission_list["builders"] = ([ "/" : "rw" ]);
}
