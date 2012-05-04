/**
 *  This file is a part of ncxmms2, an XMMS2 Client.
 *
 *  Copyright (C) 2011-2012 Pavel Kunavin <tusk.kun@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#ifndef WINDOW_P_H
#define WINDOW_P_H

#include <curses.h>
#include <vector>

#include "painter_p.h"

namespace ncxmms2 {

class Window;

class WindowPrivate
{
public:
    WindowPrivate(int lines_, int cols_, int yPos_, int xPos_, Window *parent_) :
        parent(parent_),
        focusedWindow(NULL),
        lines(lines_),
        cols(cols_),
        yPos(yPos_),
        xPos(xPos_),
        isVisible(true),
        painterPrivate(nullptr, nullptr),
        isPainterPrivateAlreadyInUse(false){}

    WINDOW *cursesWin;
    Window *parent;
    std::vector<Window*> childrenWins;
    Window *focusedWindow;

    int lines;
    int cols;

    int yPos;
    int xPos;

    bool isVisible;

    std::string title;

    PainterPrivate painterPrivate;
    bool isPainterPrivateAlreadyInUse;
};
} // ncxmms2

#endif // WINDOW_P_H
