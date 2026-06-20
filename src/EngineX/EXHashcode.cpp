#include "EngineX/EXHashcode.h"

// guessing that this should equal something like this
// possible split issue? or possibly stripped? who knows lol
// char* EXHT::HashCodeNotFoundMessage = "Hash code not found";

// objdiff difference is probably caused by the symbol mangling being wrong

char* EXHashCodeFile::Debug_HashCodeName(EXHashCode HashRef)
{
    return EXHT::HashCodeNotFoundMessage;
}
