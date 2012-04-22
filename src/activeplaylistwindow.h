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

#ifndef ACTIVEPLAYLISTWINDOW_H
#define ACTIVEPLAYLISTWINDOW_H

#include "playlistwindow.h"

namespace ncxmms2 {

class ActivePlaylistWindow : public PlaylistWindow
{
public:
    ActivePlaylistWindow(Xmms::Client *xmmsClient, int lines, int cols, int yPos, int xPos, Window *parent = nullptr);

private:
    // Settings
    bool m_autoScrollToActiveSong;

    bool getActivePlaylist(const std::string& playlist);
    void scrollToActiveSong(int item);
};
} // ncxmms2

#endif // ACTIVEPLAYLISTWINDOW_H