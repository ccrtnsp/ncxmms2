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

#include <xmmsclient/xmmsclient++.h>

#include "xmmsutils.h"
#include "settings.h"
#include "commandlineoptions.h"
#include "mainwindow/mainwindow.h"

#include "lib/application.h"
#include "lib/exceptions.h"

int main(int argc, char **argv)
{
    ncxmms2::CommandLineOptions options(argc, argv);
    if (options.parsingErrored()) {
        std::cerr << "Option parsing failed: " << options.errorString() << std::endl;
        return EXIT_FAILURE;
    }

    const std::string ipcPath = options.ipcPath().empty()
                                ? ncxmms2::Settings::value<std::string>("General", "ipcpath")
                                : options.ipcPath();

    std::unique_ptr<Xmms::Client> xmmsClient = ncxmms2::XmmsUtils::clientCreateAndConnect(ipcPath);
    if (!xmmsClient)
        return EXIT_FAILURE;

    try
    {
        ncxmms2::Application::init(options.useColors());
        ncxmms2::Application::setMainWindow(new ncxmms2::MainWindow(xmmsClient.get()));
        ncxmms2::Application::run();
        ncxmms2::Application::shutdown();
    }
    catch (Xmms::connection_error& error)
    {
        ncxmms2::Application::shutdown();
        std::cerr << "Connection failed: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (ncxmms2::DesiredWindowSizeTooSmall& error)
    {
        ncxmms2::Application::shutdown();
        std::cerr << "Terminal too small!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
