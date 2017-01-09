
#include "GaudiKernel/DeclareFactoryEntries.h"

#include "../MyAlg.h"

DECLARE_ALGORITHM_FACTORY( MyAlg )


#include "../MyAlg_2.h"
DECLARE_ALGORITHM_FACTORY( MyAlg_2 )

DECLARE_FACTORY_ENTRIES( MyPackage1 ) 
{
  DECLARE_ALGORITHM( MyAlg_2 );
  DECLARE_ALGORITHM( MyAlg );
}
