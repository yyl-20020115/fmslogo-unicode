#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "eraseproceduredialog.h"

   #include "localizedstrings.h"
   #include "wrksp.h"  // for lerase
   #include "eval.h"   // for process_special_conditions
#endif

// ----------------------------------------------------------------------------
// CEraseProcedureDialog
// ----------------------------------------------------------------------------

CEraseProcedureDialog::CEraseProcedureDialog(
    wxWindow * Parent
    )
    : CSelectProcedureDialog(Parent, LOCALIZED_ERASEPROCEDURE)
{
}

void
CEraseProcedureDialog::OnChoice(struct NODE * Procedures)
{
    // Erase the procedure.
    lerase(Procedures);

    // Handle any errors that may have occured.
    process_special_conditions();
}

BEGIN_EVENT_TABLE(CEraseProcedureDialog, CSelectProcedureDialog)
END_EVENT_TABLE()
