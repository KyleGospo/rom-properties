/***************************************************************************
 * ROM Properties Page shell extension. (GTK+ common)                      *
 * SystemsTab.hpp: Systems tab for rp-config.                              *
 *                                                                         *
 * Copyright (c) 2017-2022 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_GTK_CONFIG_SYSTEMSTAB_HPP__
#define __ROMPROPERTIES_GTK_CONFIG_SYSTEMSTAB_HPP__

#include "gtk-compat.h"

G_BEGIN_DECLS

#define RP_TYPE_SYSTEMS_TAB (rp_systems_tab_get_type())
#if GTK_CHECK_VERSION(3,0,0)
G_DECLARE_FINAL_TYPE(RpSystemsTab, rp_systems_tab, RP, SYSTEMS_TAB, GtkBox)
#else /* !GTK_CHECK_VERSION(3,0,0) */
G_DECLARE_FINAL_TYPE(RpSystemsTab, rp_systems_tab, RP, SYSTEMS_TAB, GtkVBox)
#endif /* GTK_CHECK_VERSION(3,0,0) */

/* this function is implemented automatically by the G_DEFINE_TYPE macro */
void		rp_systems_tab_register_type	(GtkWidget *widget) G_GNUC_INTERNAL;

GtkWidget	*rp_systems_tab_new		(void) G_GNUC_INTERNAL G_GNUC_MALLOC;

G_END_DECLS

#endif /* __ROMPROPERTIES_GTK_CONFIG_SYSTEMSTAB_HPP__ */
