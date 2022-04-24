#include "ScriptablePet/Actions/PetAction.h"

auto g_PetAction_Decl = ClassDecl<PetAction>()
    .Super<PetElement>()
    .Destructible()
    .Declare();