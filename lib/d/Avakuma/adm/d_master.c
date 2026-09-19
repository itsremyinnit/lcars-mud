// /d/Avakuma/adm/d_master.c: access rules for the Avakuma domain.
// Defaults from the base: Avakuma objects may write data/, everyone else reads.
// Admins always have full access through the main master.
//
// This file must exist BEFORE [Avakuma] is added to /adm/etc/groups.
// A domain entry without its master fails the groups parse and the
// master shuts the MUD down at boot.
inherit "/adm/obj/master/d_master";

void create() {
    ::create();
    // To let a wizard build here, add them below, e.g.
    //   group_list["jarrod"] = "builders";
    permission_list["builders"] = ([ "/" : "rw" ]);
}
