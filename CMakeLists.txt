cmake_minimum_required(VERSION 3.22)

# Wersję można nadpisać z linii poleceń / CI:  -DBASSORA_VERSION=1.2.3
set(BASSORA_VERSION "0.4.0" CACHE STRING "Plugin version (MAJOR.MINOR.PATCH)")
option(BASSORA_COPY_AFTER_BUILD "Copy the built plugin to the system plugin folder after building" ON)

# Windows: statyczne CRT, żeby wtyczka działała bez instalowania Visual C++ Redistributable
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(BASSORA VERSION ${BASSORA_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version")

# --- JUCE (pobierany automatycznie przy pierwszej konfiguracji) ---
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.4
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(JUCE)

set(BASSORA_FORMATS VST3 Standalone)
if(APPLE)
    list(APPEND BASSORA_FORMATS AU)
endif()

# --- grafiki osadzane w pliku wtyczki (logo w nagłówku GUI) ---
juce_add_binary_data(BassoraAssets SOURCES
    Assets/emblem.png
    Assets/wordmark.png)
set_target_properties(BassoraAssets PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

juce_add_plugin(BASSORA
    COMPANY_NAME                "BASSORA Audio"
    BUNDLE_ID                   com.bassoraaudio.bassora
    IS_SYNTH                    TRUE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD     ${BASSORA_COPY_AFTER_BUILD}
    PLUGIN_MANUFACTURER_CODE    Bsra
    PLUGIN_CODE                 Bsr1
    FORMATS                     ${BASSORA_FORMATS}
    ICON_BIG                    "${CMAKE_CURRENT_SOURCE_DIR}/Assets/icon.png"
    PRODUCT_NAME                "BASSORA")

target_sources(BASSORA PRIVATE
    Source/BassVoice.h
    Source/Dsp.h
    Source/FactoryPresets.h
    Source/Parameters.h
    Source/Theme.h
    Source/Widgets.h
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp)

target_compile_definitions(BASSORA PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(BASSORA
    PRIVATE
        BassoraAssets
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
