////////////////////////////////////////////////////////////////////////////////
//            Copyright (C) 2004-2011 by The Allacrost Project
//            Copyright (C) 2012-2015 by Bertram (Valyria Tear)
//                         All Rights Reserved
//
// This code is licensed under the GNU GPL version 2. It is free software
// and you may modify it and/or redistribute it under the terms of this license.
// See http://www.gnu.org/copyleft/gpl.html for details.
////////////////////////////////////////////////////////////////////////////////

/** ****************************************************************************
*** \file    pause.h
*** \author  Tyler Olsen, roots@allacrost.org
*** \author  Yohann Ferreira, yohann ferreira orange fr
*** \brief   Header file for pause mode interface.
*** ***************************************************************************/

#ifndef __PAUSE_HEADER__
#define __PAUSE_HEADER__

#include "engine/mode_manager.h"

#include "common/options_handler.h"
#include "common/gui/option.h"

//! \brief All calls to pause mode are wrapped in this namespace.
namespace vt_pause
{

//! \brief Determines whether the code in the vt_pause namespace should print debug statements or not.
extern bool PAUSE_DEBUG;

/** ****************************************************************************
*** \brief Handles the game operation after a pause or quit request from the player
***
*** This mode is normally entered when the player inputs a pause or quit command.
*** This class uses a captured screen image as its background and displays either
*** the text "Paused" or a quit options menu depending on the state that the mode
*** is set in. The constructor also allows you the option to automatically pause
*** the audio while the game is in this mode of operation.
***
*** When the quit state is active, the player can choose between three options:
*** - Quit Game         :: Exits the application entirely
*** - Quit to Main Menu :: Returns to boot mode, emptying the game stack in the process
*** - Cancel            :: Unpauses the game
***
*** \note When the user enters this mode, the game will sleep for small periods
*** of time so that the application isn't using up 100% of the CPU.
***
*** \note If the user inputs another quit event when this mode is active and in the
*** quit state, the game will exit immediately. If the user inputs a quit event
*** when the quit state is not active, this will activate the quite state.
*** ***************************************************************************/
class PauseMode : public vt_mode_manager::GameMode
{
public:
    /** \brief The class constructor determines the state and settings that PauseMode should be created in
    *** \param quit_state If set to true, the user will be presented with quit options
    *** \param pause_audio If set to true, the audio is paused when PauseMode becomes active and resumes when it exits.
    **/
    PauseMode(bool quit_state, bool pause_audio = false);

    ~PauseMode();

    //! \brief Resets appropriate class members. Called whenever PauseMode is made the active game mode.
    void Reset();

    //! \brief Updates the game state by the amount of time that has elapsed
    void Update();

    // Everything is drawn in post effects
    void Draw()
    {}

    //! \brief Draws the next frame to be displayed on the screen, bunt unaffected but ambient effects
    void DrawPostEffects();

    //! \brief Reload the different translated texts
    void ReloadTranslatedTexts();

private:
    //! \brief When true, the player is presented with quit options. When false, "Paused" is displayed on the screen
    bool _quit_state;

    //! \brief Set to true if the audio should be resumed when this mode finishes
    bool _audio_paused;

    //! \brief The original music volume. Used to restore it when quitting the pause mode.
    float _music_volume;

    //! \brief A screen capture of the last frame rendered on the screen before PauseMode was invoked
    vt_video::StillImage _screen_capture;

    //! \brief The color used to dim the background screen capture image
    vt_video::Color _dim_color;

    //! \brief "PAUSED" rendered as a text image texture
    vt_video::TextImage _paused_text;

    //! \brief The list of selectabled quit options presented to the user while the mode is in the quit state
    vt_gui::OptionBox _quit_options;

    //! \brief Tells whether an option has been selected, thus preventing the quick triggering of another one.
    bool _option_selected;

    //! \brief The options permitting to change different settings.
    vt_gui::private_gui::GameOptionsMenuHandler _options_handler;

    //! \brief Load or reload the menu options
    void _SetupOptions();

}; // class PauseMode : public vt_mode_manager::GameMode

} // namespace vt_pause

#endif // __PAUSE_HEADER__
