#include "ScriptablePet/PetElementFactory.h"


PetElementFactory& PetElementFactory::GetInstance()
{
    static PetElementFactory s_Instance;
    return s_Instance;
}


PetElementType<PetElement> g_PetElementType;