//
// ServoUnityWindowGL.h
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at https ://mozilla.org/MPL/2.0/.
//
// Copyright (c) 2019-2020 Mozilla, Inc.
//
// Author(s): Philip Lamb
//

#pragma once
#include "ServoUnityWindow.h"
#ifdef SUPPORT_OPENGL_CORE
#include <cstdint>
#include <string>
#include "simpleservo.h"

class ServoUnityWindowGL : public ServoUnityWindow
{
private:
	Size m_size;
	uint32_t m_texID;
	uint8_t *m_buf;
	int m_format;
	uint32_t m_pixelIntFormatGL;
	uint32_t m_pixelFormatGL;
	uint32_t m_pixelTypeGL;
	uint32_t m_pixelSize;
    PFN_WINDOWCREATEDCALLBACK m_windowCreatedCallback;
    PFN_WINDOWRESIZEDCALLBACK m_windowResizedCallback;
    PFN_BROWSEREVENTCALLBACK m_browserEventCallback;
    bool m_servoGLInited;
    bool m_servoUpdatePending;

    static void on_load_started(void);
    static void on_load_ended(void);
    static void on_title_changed(const char *title);
    static bool on_allow_navigation(const char *url);
    static void on_url_changed(const char *url);
    static void on_history_changed(bool can_go_back, bool can_go_forward);
    static void on_animating_changed(bool animating);
    static void on_shutdown_complete(void);
    static void on_ime_state_changed(bool show);
    static const char *get_clipboard_contents(void);
    static void set_clipboard_contents(const char *contents);
    static void on_media_session_metadata(const char *title, const char *album, const char *artist);
    static void on_media_session_playback_state_change(CMediaSessionPlaybackState state);
    static void on_media_session_set_position_state(double duration, double position, double playback_rate);
    static void prompt_alert(const char *message, bool trusted);
    static CPromptResult prompt_ok_cancel(const char *message, bool trusted);
    static CPromptResult prompt_yes_no(const char *message, bool trusted);
    static const char *prompt_input(const char *message, const char *def, bool trusted);
    static void on_devtools_started(CDevtoolsServerState result, unsigned int port);
    static void show_context_menu(const char *title, const char *const *items_list, uint32_t items_size);
    static void on_log_output(const char *buffer, uint32_t buffer_length);
    static void wakeup(void);

public:
	static void initDevice();
	static void finalizeDevice();
    static ServoUnityWindowGL *s_servo;
	ServoUnityWindowGL(int uid, int uidExt, Size size);
	~ServoUnityWindowGL() ;

	bool init(PFN_WINDOWCREATEDCALLBACK windowCreatedCallback, PFN_WINDOWRESIZEDCALLBACK windowResizedCallback, PFN_BROWSEREVENTCALLBACK browserEventCallback) override;
    RendererAPI rendererAPI() override {return RendererAPI::OpenGLCore;}
	Size size() override;
	void setSize(Size size) override;
	void setNativePtr(void* texPtr) override;
	void* nativePtr() override;

    // Also update the browser the next time requestUpdate() runs.
    void requestBrowserUpdate();

	// Must be called from render thread.
	void requestUpdate(float timeDelta) override;

	int format() override { return m_format; }

	void CloseServoWindow() override {}
	void pointerEnter() override;
	void pointerExit() override;
	void pointerOver(int x, int y) override;
	void pointerPress(int x, int y) override;
	void pointerRelease(int x, int y) override;
	void pointerScrollDiscrete(int x, int y) override;

	void keyPress(int charCode) override;
};

#endif // SUPPORT_OPENGL_CORE
