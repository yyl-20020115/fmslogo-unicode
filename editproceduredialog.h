// -*- c++ -*-

#include "selectproceduredialog.h"

class CEditProcedureDialog : public CSelectProcedureDialog
{
public:
    CEditProcedureDialog(wxWindow *Parent);

protected:
    virtual void OnChoice(struct NODE * Procedures);

private:
    DECLARE_NO_COPY_CLASS(CEditProcedureDialog);
    DECLARE_EVENT_TABLE();
};
