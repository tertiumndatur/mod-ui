/*
 * MOD-UI utilities
 * Copyright (C) 2015 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the COPYING file.
 */

#ifndef MOD_UTILS_H_INCLUDED
#define MOD_UTILS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define MOD_API __attribute__ ((visibility("default")))

typedef struct {
    const char* name;
    const char* homepage;
    const char* email;
} PluginAuthor;

typedef struct {
    bool valid;
    int index;
    const char* name;
    const char* symbol;
} PluginGUIPort;

typedef struct {
    const char* resourcesDirectory;
    const char* iconTemplate;
    const char* settingsTemplate;
    const char* javascript;
    const char* stylesheet;
    const char* screenshot;
    const char* thumbnail;
    const char* brand;
    const char* label;
    const char* model;
    const char* panel;
    const char* color;
    const char* knob;
    PluginGUIPort* ports;
} PluginGUI;

typedef struct {
    const char* screenshot;
    const char* thumbnail;
} PluginGUI_Mini;

typedef struct {
    float min;
    float max;
    float def;
} PluginPortRanges;

typedef struct {
    const char* label;
    const char* render;
    const char* symbol;
    bool _custom;
} PluginPortUnits;

typedef struct {
    bool valid;
    float value;
    const char* label;
} PluginPortScalePoint;

typedef struct {
    bool valid;
    unsigned int index;
    const char* name;
    const char* symbol;
    PluginPortRanges ranges;
    PluginPortUnits units;
    const char* designation;
    const char* const* properties;
    int rangeSteps;
    const PluginPortScalePoint* scalePoints;
    const char* shortname;
} PluginPort;

typedef struct {
    PluginPort* input;
    PluginPort* output;
} PluginPortsI;

typedef struct {
    PluginPortsI audio;
    PluginPortsI control;
    PluginPortsI cv;
    PluginPortsI midi;
} PluginPorts;

typedef struct {
    bool valid;
    const char* uri;
    const char* label;
} PluginPreset;

typedef struct {
    bool valid;
    const char* uri;
    const char* name;
    const char* binary;
    const char* brand;
    const char* label;
    const char* license;
    const char* comment;
    const char* const* category;
    int microVersion;
    int minorVersion;
    int release;
    const char* version;
    const char* stability;
    PluginAuthor author;
    const char* const* bundles;
    PluginGUI gui;
    PluginPorts ports;
    const PluginPreset* presets;
} PluginInfo;

typedef struct {
    bool valid;
    const char* uri;
    const char* name;
    const char* brand;
    const char* label;
    const char* comment;
    const char* const* category;
    int microVersion;
    int minorVersion;
    int release;
    PluginGUI_Mini gui;
} PluginInfo_Mini;

typedef struct {
    bool valid;
    const char* symbol;
    float value;
} PedalboardPluginPort;

typedef struct {
    bool valid;
    const char* instance;
    const char* uri;
    bool bypassed;
    float x;
    float y;
    const PedalboardPluginPort* ports;
} PedalboardPlugin;

typedef struct {
    bool valid;
    const char* source;
    const char* target;
} PedalboardConnection;

typedef struct {
    const char* const* audio_ins;
    const char* const* audio_outs;
    const char* const* midi_ins;
    const char* const* midi_outs;
} PedalboardHardware;

typedef struct {
    const char* title;
    const PedalboardPlugin* plugins;
    const PedalboardConnection* connections;
    PedalboardHardware hardware;
} PedalboardInfo;

typedef struct {
    bool valid;
    const char* uri;
    const char* bundle;
    const char* title;
} PedalboardInfo_Mini;

typedef struct {
    bool valid;
    const char* symbol;
    float value;
} StatePortValue;

// initialize
MOD_API void init(void);

// cleanup, cannot be used afterwards
MOD_API void cleanup(void);

// add a bundle to our lilv world
// returns uri list of added plugins (null for none)
MOD_API const char* const* add_bundle_to_lilv_world(const char* bundle);

// remove a bundle from our lilv world
// returns uri list of removed plugins (null for none)
MOD_API const char* const* remove_bundle_from_lilv_world(const char* bundle);

// get all available plugins
// this triggers scanning of all plugins
MOD_API const PluginInfo_Mini* const* get_all_plugins(void);

// get a specific plugin
// NOTE: may return null
MOD_API const PluginInfo* get_plugin_info(const char* uri);

// get a specific plugin (mini)
// NOTE: may return null
MOD_API const PluginInfo_Mini* get_plugin_info_mini(const char* uri);

// get all control input ports for a specific plugin
MOD_API const PluginPort* get_plugin_control_input_ports(const char* uri);

// get all available pedalboards (ie, plugins with pedalboard type)
MOD_API const PedalboardInfo_Mini* const* get_all_pedalboards(void);

// Get a specific pedalboard
// NOTE: may return null
MOD_API const PedalboardInfo* get_pedalboard_info(const char* bundle);

// Get the size of a specific pedalboard
// Returns a 2-size array with width and height
// NOTE: may return null
MOD_API int* get_pedalboard_size(const char* bundle);

// Get port values from a plugin state
MOD_API StatePortValue* get_state_port_values(const char* state);

// Convert a file URI to a local path string.
MOD_API const char* file_uri_parse(const char* fileuri);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MOD_UTILS_H_INCLUDED