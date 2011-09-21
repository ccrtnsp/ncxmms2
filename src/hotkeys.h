/**
 *  This file is a part of ncxmms2, an XMMS2 Client.
 *
 *  Copyright (C) 2011 Pavel Kunavin <tusk.kun@gmail.com>
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

#ifndef HOTKEYS_H
#define HOTKEYS_H

namespace ncxmms2
{
	namespace Hotkeys
	{	
		const int Quit = 'q';
		
		// Screens switching
		const int PlaylistScreen               = '2';
		const int LocalFileSystemBrowserScreen = '3';
		const int PlaylistsBrowserScreen       = '6';
		
		// Playback control
		const int PlaybackToggle       = 'P';
		const int PlaybackStop         = 's';
		const int PlaybackNext         = '>';
		const int PlaybackPrev         = '<';
		const int PlaybackSeekForward  = 'f';
		const int PlaybackSeekBackward = 'b';
		
	}
}
#endif // HOTKEYS_H
