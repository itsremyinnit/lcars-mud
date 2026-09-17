// /d/Nexus/adm/d_master.c: access rules for the Nexus domain.
// Defaults from the base: Nexus objects may write data/, everyone else reads.
// Admins always have full access through the main master.
inherit "/adm/obj/master/d_master";

void create() {
    ::create();
    // To let a wizard build here, add them below, e.g.
    //   group_list["jarrod"] = "builders";
    permission_list["builders"] = ([ "/" : "rw" ]);
}
