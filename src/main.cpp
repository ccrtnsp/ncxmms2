/**
 *  This file is a part of ncxmms2, an XMMS2 Client.
 *
 *  Copyright (C) 2011-2013 Pavel Kunavin <tusk.kun@gmail.com>
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

#include <glib.h>
#include <xmmsclient/xmmsclient++.h>

#include "config.h"
#include "log.h"
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
        if (options.useColors()) {
            // Try user color scheme config
            const std::string userColorSchemeFilePath =
                    std::string(g_get_user_config_dir()).append("/ncxmms2/ncxmms2.colors");
            if (g_file_test(userColorSchemeFilePath.c_str(), G_FILE_TEST_EXISTS)) {
                ncxmms2::Application::setColorSchemeFile(userColorSchemeFilePath);
            } else {
                // Try global color scheme config
                const std::string globalColorSchemeFilePath =
                        std::string(CMAKE_INSTALL_PREFIX "/share/ncxmms2/ncxmms2.colors");
                if (g_file_test(globalColorSchemeFilePath.c_str(), G_FILE_TEST_EXISTS)) {
                    ncxmms2::Application::setColorSchemeFile(globalColorSchemeFilePath);
                }
            }
        }

        ncxmms2::Window *mainWindow = new ncxmms2::MainWindow(xmmsClient.get());
        ncxmms2::Application::setMainWindow(mainWindow);
        mainWindow->show();
        ncxmms2::Application::run();
        ncxmms2::Application::shutdown();
    }
    catch (const Xmms::connection_error& error)
    {
        ncxmms2::Application::shutdown();
        std::cerr << "Connection failed: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const ncxmms2::DesiredWindowSizeTooSmall& error)
    {
        ncxmms2::Application::shutdown();
        std::cerr << "Terminal too small!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error& error)
    {
        ncxmms2::Application::shutdown();
        std::cerr << "Runtime error: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
