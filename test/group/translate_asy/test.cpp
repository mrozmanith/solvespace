#include "harness.h"

TEST_CASE(normal_roundtrip) {
    CHECK_LOAD("normal.slvs");
    CHECK_RENDER_ISO("normal.png");
    CHECK_SAVE("normal.slvs");
}

TEST_CASE(normal_inters) {
    CHECK_LOAD("normal.slvs");

    Group *g = SK.GetGroup(SS.GW.activeGroup);
    SMesh *m = &g->displayMesh;

    SEdgeList el = {};
    bool inters, leaks;
    SKdNode::From(m)->MakeCertainEdgesInto(&el,
        EdgeKind::SELF_INTER, /*coplanarIsInter=*/false, &inters, &leaks);

    // The assembly is supposed to interfere.
    CHECK_TRUE(inters);
}
