/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TabPageRegisters.h"

namespace Modbus {

TabPageRegisters::TabPageRegisters(wxWindow *parent)
    : wxDataViewListCtrl(parent, wxID_ANY)
{
    AppendTextColumn(_("Address"),
                     wxDATAVIEW_CELL_INERT,
                     100,
                     wxALIGN_CENTRE,
                     wxDATAVIEW_COL_RESIZABLE);
    AppendTextColumn(_("Format"),
                     wxDATAVIEW_CELL_EDITABLE,
                     100,
                     wxALIGN_CENTRE,
                     wxDATAVIEW_COL_RESIZABLE);
    AppendTextColumn(_("Name"),
                     wxDATAVIEW_CELL_EDITABLE,
                     200,
                     wxALIGN_CENTRE,
                     wxDATAVIEW_COL_RESIZABLE);
    AppendTextColumn(_("Value"),
                     wxDATAVIEW_CELL_EDITABLE,
                     100,
                     wxALIGN_CENTRE,
                     wxDATAVIEW_COL_RESIZABLE);
    AppendTextColumn(_("Description"),
                     wxDATAVIEW_CELL_EDITABLE,
                     100,
                     wxALIGN_LEFT,
                     wxDATAVIEW_COL_RESIZABLE);

    wxVector<wxVariant> data;
    for (int i = 0; i < 5; ++i) {
        data.clear();
        data.push_back(wxString::Format("R%dC1", i + 1));
        data.push_back(wxString::Format("R%dC2", i + 1));
        data.push_back(wxString::Format("R%dC3", i + 1));
        data.push_back(wxString::Format("R%dC4", i + 1));
        data.push_back(wxString::Format("R%dC5", i + 1));
        AppendItem(data);
    }

    //Bind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, &TabPageRegisters::OnEditingDone, this);
};

TabPageRegisters::~TabPageRegisters() {}

} // namespace Modbus
