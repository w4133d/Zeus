// Zeus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "BSPConverter.h"
#include <conio.h>

// Gets the path of this app
std::filesystem::path GetExePath()
{
    char appPath[ MAX_PATH + 1 ];
    GetModuleFileNameA( NULL, appPath, MAX_PATH );
    return std::filesystem::path( appPath );
}

std::filesystem::path GetBo3Path()
{
    char path[ MAX_PATH + 1 ];

    if( !GetEnvironmentVariableA( "TA_TOOLS_PATH", path, MAX_PATH ) )
        throw std::exception( "Failed to located Black Ops III's folder" );

    return std::filesystem::path( path );
}

void ShowHelp()
{
    PLX::Printer::WriteLineHeader( "HELP", "To use drag and drop files to convert." );
    PLX::Printer::WriteLineHeader( "HELP", "Args:" );
    PLX::Printer::WriteLineHeader( "HELP", "\t-noexportxme\t\t- Don't export xmodel_export" );
    PLX::Printer::WriteLineHeader( "HELP", "\t-noexportobj\t\t- Don't export obj" );
}

int main( int argc, char **argv )
{
    PLX::Printer::WriteLineHeader( "INIT", "-------------------------------------" );
    PLX::Printer::WriteLineHeader( "INIT", "Zeus by Scobalula" );
    PLX::Printer::WriteLineHeader( "INIT", "Black Ops III D3DBSP Converter" );
    PLX::Printer::WriteLineHeader( "INIT", "Version: 1.0.2.0 - Rayjiun Sexy Edition" );
    PLX::Printer::WriteLineHeader( "INIT", "Modified by prov3ntus" );
    PLX::Printer::WriteLineHeader( "INIT", "-------------------------------------" );

    auto exeDir = GetExePath().parent_path().string();

    BSPConverter::Settings settings;

    for( int i = 1; i < argc; i++ )
    {
        std::string asStr = argv[ i ];
        std::filesystem::path asPath( asStr );
        auto extension = asPath.extension();

        if( extension == ".d3dbsp" )
        {
            settings.BSPFiles.emplace_back( asStr );
        }
        else if( extension == ".map" )
        {
            settings.MapFiles.emplace_back( asStr );
        }
        else if( asStr == "-noexportobj" )
        {
            settings.Values[ "ToOBJ" ] = "No";
        }
        else if( asStr == "-noexportxme" )
        {
            settings.Values[ "ToXME" ] = "No";
        }
        else if( asStr == "-nocleanup" )
        {
            settings.Values[ "Clean" ] = "No";
        }
    }

    size_t filesProcessed = 0;

    // We want to process .map files first for consecutive processing of the .d3dbsp output - pv
    // For map files, just invoke the compiled
    for( auto &file : settings.MapFiles )
    {
        try
        {
            auto name = std::filesystem::path( file ).filename().string();
            auto bo3Path = GetBo3Path().string();

            auto cod2MapPath = bo3Path + "\\bin\\cod2map64.exe";
            auto outputPath = bo3Path + "\\share\\raw\\maps\\" + name.substr( 0, name.find_last_of( '.' ) ) + ".d3dbsp";
            auto params = "-platform pc -navmesh -navvolume -loadFrom \"" + file + "\" \"" + outputPath + "\"";

            PLX::Printer::WriteLineHeader( "MAPConvert", "Passing '%s' to BSP compiler...", name.c_str() );

            SHELLEXECUTEINFOA execInfo = { 0 };
            execInfo.cbSize = sizeof( SHELLEXECUTEINFOA );
            execInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            execInfo.hwnd = NULL;
            execInfo.lpVerb = NULL;
            execInfo.lpFile = cod2MapPath.c_str();
            execInfo.lpParameters = params.c_str();
            execInfo.lpDirectory = NULL;
            execInfo.nShow = SW_SHOW;
            execInfo.hInstApp = NULL;
            ShellExecuteExA( &execInfo );
            WaitForSingleObject( execInfo.hProcess, INFINITE );
            CloseHandle( execInfo.hProcess );

            settings.BSPFiles.emplace_back( outputPath );

            PLX::Printer::WriteLineHeader( "MAPConvert", "%s passed successfully", name.c_str() );
        }
        catch( const std::exception &e )
        {
            PLX::Printer::WriteLineHeader( "ERROR", "Error: %s", e.what() );
        }

        filesProcessed++;
    }

    for( auto &file : settings.BSPFiles )
    {
        try
        {
            auto name = std::filesystem::path( file ).filename().string();

            PLX::Printer::WriteLineHeader( "BSPLoader", "Processing %s...", name.c_str() );

            BSPConverter bspConverter( file, settings );

            bspConverter.Save( exeDir + "\\Converted Files", name, settings );
        }
        catch( const std::exception &e )
        {
            PLX::Printer::WriteLineHeader( "ERROR", "Error: %s", e.what() );
        }

        filesProcessed++;
    }

    // Clean up any temporary .d3dbsp files from .map conversions created by Zeus - pv
    if( settings.GetSettingValue( "Clean", "Yes" ) == "Yes" )
    {
        auto bo3_path = GetBo3Path().string();
        
        for( auto &file : settings.MapFiles )
        {
            try
            {
                auto name = std::filesystem::path( file ).filename().string();
                auto bsp_name = name.substr( 0, name.find_last_of( '.' ) ) + ".d3dbsp";
                auto bsp_path = bo3_path + "\\share\\raw\\maps\\" + bsp_name;

                if( std::remove( bsp_path.c_str() ) == 0 )
                {
                    PLX::Printer::WriteLineHeader( "Clean-Up", "Successfully cleaned up temporary file '%s'", bsp_name.c_str() );
                }
                else
                {
                    PLX::Printer::WriteLineHeader( "ERROR", "Failed to clean up temporary file '%s'", bsp_name.c_str() );
                }
            }
            catch( const std::exception &e )
            {
                PLX::Printer::WriteLineHeader( "ERROR", "Error: %s", e.what() );
            }
        }
    }

    if( filesProcessed == 0 )
    {
        PLX::Printer::WriteLineHeader( "ERROR", "No files provided to convert" );
        ShowHelp();
    }

    PLX::Printer::WriteLineHeader( "CONSOLE", "Execution complete, press any key to exit." );

    _getch();

    return 0;
}
