/*****************************************************************************
 * ROM Properties Page shell extension. (GTK+ 3.x)                           *
 * ThunarPropertyPageProvider.hpp: ThunarX Property Page Provider Definition *
 *                                                                           *
 * Copyright (c) 2017-2022 by David Korth.                                   *
 * SPDX-License-Identifier: GPL-2.0-or-later                                 *
 *****************************************************************************/

#pragma once

#include "glib-compat.h"
#include "ThunarPlugin.hpp"

G_BEGIN_DECLS

#define RP_TYPE_THUNAR_PROPERTY_PAGE_PROVIDER (rp_thunar_property_page_provider_get_type())
G_DECLARE_FINAL_TYPE(RpThunarPropertyPageProvider, rp_thunar_property_page_provider, RP, THUNAR_PROPERTY_PAGE_PROVIDER, GObject)

/* this function is implemented automatically by the G_DEFINE_TYPE macro */
/* NOTE: G_DEFINE_DYNAMIC_TYPE() declares the actual function as static. */
void rp_thunar_property_page_provider_register_type_ext(ThunarxProviderPlugin *plugin) G_GNUC_INTERNAL;

G_END_DECLS
