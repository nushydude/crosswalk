// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Multiply-included file, no traditional include guard.
#include <string>

#include "xwalk/runtime/common/android/xwalk_hit_test_data.h"
#include "content/public/common/common_param_traits.h"
#include "ipc/ipc_channel_handle.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/base/page_transition_types.h"
#include "ui/gfx/geometry/point_f.h"
#include "ui/gfx/geometry/size_f.h"


// Singly-included section for enums and custom IPC traits.
#ifndef XWALK_RUNTIME_COMMON_ANDROID_XWALK_RENDER_VIEW_MESSAGES_H_
#define XWALK_RUNTIME_COMMON_ANDROID_XWALK_RENDER_VIEW_MESSAGES_H_

namespace IPC {

// TODO(upstream): - add enums and custom IPC traits here when needed.

}  // namespace IPC

#endif  // XWALK_RUNTIME_COMMON_ANDROID_XWALK_RENDER_VIEW_MESSAGES_H_

IPC_STRUCT_TRAITS_BEGIN(xwalk::XWalkHitTestData)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(extra_data_for_type)
  IPC_STRUCT_TRAITS_MEMBER(href)
  IPC_STRUCT_TRAITS_MEMBER(anchor_text)
  IPC_STRUCT_TRAITS_MEMBER(img_src)
IPC_STRUCT_TRAITS_END()

#define IPC_MESSAGE_START AndroidWebViewMsgStart

//-----------------------------------------------------------------------------
// RenderView messages
// These are messages sent from the browser to the renderer process.

// Tells the renderer to drop all WebCore memory cache.
IPC_MESSAGE_CONTROL0(XWalkViewMsg_ClearCache) // NOLINT(*)

// Request for the renderer to determine if the document contains any image
// elements.  The id should be passed in the response message so the response
// can be associated with the request.
IPC_MESSAGE_ROUTED1(XWalkViewMsg_DocumentHasImages, // NOLINT(*)
                    int /* id */)

// Do hit test at the given webview coordinate. "Webview" coordinates are
// physical pixel values with the 0,0 at the top left of the current displayed
// view (ie 0,0 is not the top left of the page if the page is scrolled).
IPC_MESSAGE_ROUTED2(XWalkViewMsg_DoHitTest, // NOLINT(*)
                    gfx::PointF /* touch_center */,
                    gfx::SizeF /* touch_area */)

// Enables receiving pictures from the renderer on every new frame.
IPC_MESSAGE_ROUTED1(XWalkViewMsg_EnableCapturePictureCallback, // NOLINT(*)
                    bool /* enable */)

// Requests a new picture with the latest renderer contents synchronously.
// This message blocks the browser process on the renderer until complete.
IPC_SYNC_MESSAGE_ROUTED0_0(XWalkViewMsg_CapturePictureSync) // NOLINT(*)

// Sets the zoom level for text only. Used in layout modes other than
// Text Autosizing.
IPC_MESSAGE_ROUTED1(XWalkViewMsg_SetTextZoomLevel, // NOLINT(*)
                    double /* zoom_level */)

// Resets WebKit WebView scrolling and scale state. We need to send this
// message whenever we want to guarantee that page's scale will be
// recalculated by WebKit.
IPC_MESSAGE_ROUTED0(XWalkViewMsg_ResetScrollAndScaleState) // NOLINT(*)

// Sets the initial page scale. This overrides initial scale set by
// the meta viewport tag.
IPC_MESSAGE_ROUTED1(XWalkViewMsg_SetInitialPageScale, // NOLINT(*)
                    double /* page_scale_factor */)

// Set the Javascript online property for network availability change.
IPC_MESSAGE_CONTROL1(XWalkViewMsg_SetJsOnlineProperty, bool /* network_up */) // NOLINT(*)

// Set the white list for Cross-Origin access.
IPC_MESSAGE_CONTROL2(XWalkViewMsg_SetOriginAccessWhitelist, // NOLINT(*)
                     std::string /* base url */,
                     std::string /* match pattern content*/)

// Set the background  color
IPC_MESSAGE_ROUTED1(XWalkViewMsg_SetBackgroundColor, // NOLINT(*)
                    SkColor)

// Set the text zoom factor
IPC_MESSAGE_ROUTED1(XWalkViewMsg_SetTextZoomFactor, // NOLINT(*)
                    float)

//-----------------------------------------------------------------------------
// RenderView messages
// These are messages sent from the renderer to the browser process.

// Response to XWalkViewMsg_DocumentHasImages request.
IPC_MESSAGE_ROUTED2(XWalkViewHostMsg_DocumentHasImagesResponse, // NOLINT(*)
                    int, /* id */
                    bool /* has_images */)

// Response to XWalkViewMsg_DoHitTest.
IPC_MESSAGE_ROUTED1(XWalkViewHostMsg_UpdateHitTestData, // NOLINT(*)
                    xwalk::XWalkHitTestData)

// Notification that a new picture becomes available. It is only sent if
// XWalkViewMsg_EnableCapturePictureCallback was previously enabled.
IPC_MESSAGE_ROUTED0(XWalkViewHostMsg_PictureUpdated) // NOLINT(*)

// Sent by the renderer when accelerated compositing is enabled, allowing the
// browser to perform synchronous input event filtering.
IPC_MESSAGE_ROUTED1(XWalkViewHostMsg_DidActivateAcceleratedCompositing, // NOLINT(*)
                    int /* input_handler_id */)

// Sent immediately before a top level navigation is initiated within Blink.
// There are some exclusions, the most important ones are it is not sent
// when creating a popup window, and not sent for application initiated
// navigations. See XWalkContentRendererClient::HandleNavigation for all
// cornercases. This is sent before updating the NavigationController state
// or creating a URLRequest for the main frame resource.
IPC_SYNC_MESSAGE_CONTROL5_1(XWalkViewHostMsg_ShouldOverrideUrlLoading, // NOLINT(*)
                            int /* render_frame_id id */,
                            base::string16 /* in - url */,
                            bool /* in - has_user_gesture */,
                            bool /* in - is_redirect */,
                            bool /* in - is_main_frame */,
                            bool /* out - result */)
IPC_SYNC_MESSAGE_CONTROL3_2(XWalkViewHostMsg_WillSendRequest, // NOLINT(*)
                            int /* render_frame_id id */,
                            std::string /* in - url */,
                            ui::PageTransition /*in - transition_type */,
                            std::string /* out - new url*/,
                            bool /* out - did_overwrite*/)
// Sent when a subframe is created.
IPC_MESSAGE_CONTROL2(XWalkViewHostMsg_SubFrameCreated, // NOLINT(*)
                     int, /* parent_render_frame_id */
                     int /* child_render_frame_id */)

