cmake_minimum_required( VERSION 2.8 )

project(DigitRecog)

Find_Package( SDL REQUIRED )
Find_Package( SDL_image REQUIRED )
Find_Package( SDL_mixer REQUIRED )
Find_Package( SDL_ttf REQUIRED )

if ( NOT SDL_FOUND )
    message( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

if( NOT SDLIMAGE_FOUND )
    message( FATAL_ERROR "SDL_Image not found!" )
endif( NOT SDLIMAGE_FOUND )

if( NOT SDLMIXER_FOUND )
    message( FATAL_ERROR "SDL_Mixer not found" )
endif( NOT SDLMIXER_FOUND )

if( NOT SDLTTF_FOUND )
    message( FATAL_ERROR "SDL_TTF not found" )
endif( NOT SDLTTF_FOUND )

include_directories(
  ${CMAKE_SOURCE_DIR}
  )

set( SRCS
  
  Engine/GL/glTex.cpp
  Engine/Mouse.cpp
  Engine/AI/NeuralNetwork/NeuralNetwork.cpp
  Engine/Keyboard.cpp
  Engine/Engine.cpp
  Engine/SDL/SDL_SurfacePtr.cpp
  Engine/SDL/Font.cpp
  Engine/GUI/LabeledButton.cpp
  Engine/GUI/Label.cpp
  Engine/GUI/Button.cpp
  Buttons.cpp
  Grid.cpp
  main.cpp
  App.cpp
)

add_executable(DigitRecog ${SRCS})

target_link_libraries(DigitRecog
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY}
  ${SDLMIXER_LIBRARY}
  ${SDLTTF_LIBRARY}
  GL
)

