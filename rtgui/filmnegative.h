/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _NEG_H_
#define _NEG_H_

#include <gtkmm.h>
#include "toolpanel.h"
#include "adjuster.h"
#include "guiutils.h"
#include "wbprovider.h"
#include "editcallbacks.h"
#include "../rtengine/procparams.h"


class FilmNegProvider
{
public:
    virtual ~FilmNegProvider() = default;
    virtual bool getFilmNegativeExponents(rtengine::Coord spotA, rtengine::Coord spotB, float* newExps) = 0;
};

class FilmNegative : public ToolParamBlock, public AdjusterListener, public FoldableToolPanel, public EditSubscriber
{

private:
    rtengine::ProcEvent EvFilmNegativeExponents;
    rtengine::ProcEvent EvFilmNegativeEnabled;

    std::vector<rtengine::Coord> refSpotCoords;

    FilmNegProvider *fnp;

    Adjuster* redExp;
    Adjuster* greenExp;
    Adjuster* blueExp;

    Gtk::Grid* spotgrid;
    Gtk::ToggleButton* spotbutton;
    sigc::connection spotConn;

    void editToggled ();

public:

    FilmNegative ();
    ~FilmNegative () override;

    void setFilmNegProvider(FilmNegProvider* p)
    {
        fnp = p;
    };

    void read           (const rtengine::procparams::ProcParams* pp, const ParamsEdited* pedited = nullptr) override;
    void write          (rtengine::procparams::ProcParams* pp, ParamsEdited* pedited = nullptr) override;
    void setDefaults    (const rtengine::procparams::ProcParams* defParams, const ParamsEdited* pedited = nullptr) override;
    void setBatchMode   (bool batchMode) override;

    void adjusterChanged (Adjuster* a, double newval) override;
    void adjusterAutoToggled(Adjuster* a, bool newval) override;
    void spotPressed ();
    void enabledChanged() override;

    void setEditProvider (EditDataProvider* provider) override;

    // EditSubscriber interface
    CursorShape getCursor(int objectID) const override;
    bool mouseOver(int modifierKey) override;
    bool button1Pressed(int modifierKey) override;
    bool button1Released() override;
    void switchOffEditMode () override;
    bool pick1(bool picked) override;

};

#endif
