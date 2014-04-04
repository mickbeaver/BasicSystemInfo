#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

namespace
{
   static char const * const skOutputFilename = "BasicSystemInfo.txt";
}

static void write_video_info_to_file( FILE * const outputFile )
{
   if ( SDL_Init(SDL_INIT_VIDEO) == 0 )
   {
      //int const numDrivers = SDL_GetNumVideoDrivers();
      //fprintf( outputFile, "There are %d video drivers\n", numDrivers );
      //char const *driverDescription = SDL_GetCurrentVideoDriver();
      //if ( driverDescription != NULL )
      //{
      //   fprintf( outputFile, "\tCurrent video driver: '%s'\n", driverDescription );
      //}
      //else
      //{
      //   fprintf( outputFile, "SDL_GetCurrentVideoDriver() encountered an error. SDL_GetError()='%s'\n", SDL_GetError() );
      //}
      //for ( int driverIndex = 0; driverIndex < numDrivers; ++driverIndex )
      //{
      //   driverDescription = SDL_GetVideoDriver( driverIndex );
      //   if ( driverDescription != NULL )
      //   {
      //      fprintf( outputFile, "\tDriver #%d: '%s'\n", driverIndex, driverDescription );
      //   }
      //   else
      //   {
      //      fprintf( outputFile, "SDL_GetVideoDriver() encountered an error. Driver index=%d, SDL_GetError()='%s'\n", driverIndex, SDL_GetError() );
      //   }
      //}

      int const numVideoDisplays = SDL_GetNumVideoDisplays();
      fprintf( outputFile, "There are %d video displays\n", numVideoDisplays );
      for ( int displayIndex = 0; displayIndex < numVideoDisplays; ++displayIndex )
      {
         SDL_DisplayMode displayMode;

         if ( SDL_GetCurrentDisplayMode( displayIndex, &displayMode ) == 0 )
         {
            char const *name = SDL_GetDisplayName( displayIndex );
            name = ( name == NULL ) ? "<none>" : name;
            fprintf( outputFile, "Display #%d: name='%s', current display mode=%dx%d@%dhz.\n", displayIndex, name, displayMode.w, displayMode.h, displayMode.refresh_rate);
         }
         else
         {
            fprintf( outputFile, "SDL_GetCurrentDisplayMode() encountered an error. Display #%d, SDL_GetError()='%s'\n", displayIndex, SDL_GetError() );
         }

         int const numDisplayModes = SDL_GetNumDisplayModes( displayIndex );
         fprintf( outputFile, "Display #%d has %d display modes\n", displayIndex, numDisplayModes );
         for ( int displayModeIndex = 0; displayModeIndex < numDisplayModes; ++displayModeIndex )
         {
            if ( SDL_GetDisplayMode( displayIndex, displayModeIndex, &displayMode ) == 0 )
            {
               fprintf( outputFile, "\tDisplay #%d: available display mode: %dx%d@%dhz. \n", displayIndex, displayMode.w, displayMode.h, displayMode.refresh_rate);
            }
            else
            {
               fprintf( outputFile, "\tSDL_GetDisplayMode() encountered an error. Display #%d, modeIndex=%d, SDL_GetError()='%s'\n", displayIndex, displayModeIndex, SDL_GetError() );
            }
         }
      }
      SDL_Quit();     
   }
}

int main( int argc, char* argv[] )
{
   FILE *outputFile = NULL;
   outputFile = fopen( skOutputFilename, "w" );
   if ( outputFile != NULL )
   {
      write_video_info_to_file( outputFile );
      fclose( outputFile );
   }

   return 0;   
}
