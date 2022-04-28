#include "ScriptablePet/Conditions/PetCondition.h"


auto g_PetCondition_Decl = ClassDecl<PetCondition>()
    .Super<PetElement>()
    .Destructible();