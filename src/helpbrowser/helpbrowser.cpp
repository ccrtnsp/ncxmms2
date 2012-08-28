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

#include "helpbrowser.h"
#include "../hotkeys.h"

using namespace ncxmms2;

HelpBrowser::HelpBrowser(const Rectangle& rect, Window *parent) :
    TextView(rect, parent)
{
    setName("Help");

    struct KeyDescription {const char *description; KeyEvent::key_t key;};

    const KeyDescription screensSwitchingKeys[] =
    {
        {"Help screen",                       Hotkeys::Screens::Help::Activate},
        {"Active playlist screen",            Hotkeys::Screens::ActivePlaylist::Activate},
        {"Local file system browser screen ", Hotkeys::Screens::LocalFileSystemBrowser::Activate},
        {"Medialib browser screen",           Hotkeys::Screens::MedialibBrowser::Activate},
        {"Playlists browser screen",          Hotkeys::Screens::PlaylistsBrowser::Activate},
        {nullptr, 0}
    };

    const KeyDescription playbackControlKeys[] =
    {
        {"Toggle playback", Hotkeys::Playback::Toggle},
        {"Stop",            Hotkeys::Playback::Stop},
        {"Next track",      Hotkeys::Playback::Next},
        {"Previous track",  Hotkeys::Playback::Prev},
        {"Seek forward",    Hotkeys::Playback::SeekForward},
        {"Seek backward",   Hotkeys::Playback::SeekBackward},
        {nullptr, 0}
    };

    const KeyDescription playlistViewKeys[] =
    {
        {"Remove entry",                 Hotkeys::PlaylistView::RemoveEntry},
        {"Clear playlist",               Hotkeys::PlaylistView::ClearPlaylist},
        {"Shuffle playlist",             Hotkeys::PlaylistView::ShufflePlaylist},
        {"Go to currently playing song", Hotkeys::PlaylistView::GoToCurrentlyPlayingSong},
        {"Add file or directory",        Hotkeys::PlaylistView::AddFileOrDirectory},
        {"Add url",                      Hotkeys::PlaylistView::AddUrl},
        {nullptr, 0}
    };

    const KeyDescription localFileSystemBrowserKeys[] =
    {
        {"Add file or directory to active playlist", Hotkeys::Screens::LocalFileSystemBrowser::AddFileOrDirectoryToActivePlaylist},
        {"Go up",                                    Hotkeys::Screens::LocalFileSystemBrowser::GoUp},
        {"Change directory",                         Hotkeys::Screens::LocalFileSystemBrowser::ChangeDirectory},
        {"Reload directory",                         Hotkeys::Screens::LocalFileSystemBrowser::ReloadDirectory},
        {nullptr, 0}
    };

    const KeyDescription medialibBrowserKeys[] =
    {
        {"Add item to active playlist", Hotkeys::Screens::MedialibBrowser::AddItemToActivePlaylist},
        {"Refresh",                     Hotkeys::Screens::MedialibBrowser::Refresh},
        {nullptr, 0}
    };

    const KeyDescription playlistsBrowserKeys[] =
    {
        {"Create new playlist", Hotkeys::Screens::PlaylistsBrowser::CreateNewPlaylist},
        {"Remove playlist",     Hotkeys::Screens::PlaylistsBrowser::RemovePlaylist},
        {"Rename playlist",     Hotkeys::Screens::PlaylistsBrowser::RenamePlaylist},
        {nullptr, 0}
    };

    const struct Section {const char *name; const KeyDescription *keys;} help[] =
    {
        {"Screens switching",         screensSwitchingKeys},
        {"Playback control",          playbackControlKeys},
        {"Playlist view",             playlistViewKeys},
        {"Local file system browser", localFileSystemBrowserKeys},
        {"Medialib browser",          medialibBrowserKeys},
        {"Playlists browser",         playlistsBrowserKeys}
    };

    for (const Section& section : help) {
        appendLine(std::string("      ").append(section.name));
        appendLine("---------------------------------");
        const KeyDescription *keyDesc = section.keys;
        while (keyDesc->description) {
            std::string line(5, ' ');
            line.append(KeyEvent(keyDesc->key).keyName());
            line.resize(15, ' ');
            line.append(" : ");
            line.append(keyDesc->description);
            appendLine(line);
            ++keyDesc;
        }
        appendLine();
    }
}