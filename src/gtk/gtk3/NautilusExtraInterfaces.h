/*******************************************************************************
 * ROM Properties Page shell extension. (GTK+ 3.x)                             *
 * NautilusExtraInterfaces.h: Extra interfaces in Nautilus-based file managers *
 *                                                                             *
 * Copyright (c) 2017-2023 by David Korth.                                     *
 * SPDX-License-Identifier: GPL-2.0-or-later                                   *
 *******************************************************************************/

#pragma once

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#if GTK_CHECK_VERSION(3,0,0) && !GTK_CHECK_VERSION(4,0,0)
// NOTE: We only have extra interfaces in GTK3 right now.
#  define HAVE_EXTRA_INTERFACES 1
// Nemo is GTK3 only for now.
#  define HAVE_NEMO_INTERFACES 1
#endif /* GTK_CHECK_VERSION(3,0,0) && !GTK_CHECK_VERSION(4,0,0) */

#ifdef HAVE_NEMO_INTERFACES
// Nemo-specific interfaces
struct _NemoNameAndDescProvider;
typedef struct _NemoNameAndDescProvider NemoNameAndDescProvider;

struct _NemoNameAndDescProviderInterface {
	GTypeInterface g_iface;

	GList *(*get_name_and_desc) (NemoNameAndDescProvider *provider);
};
typedef struct _NemoNameAndDescProviderInterface NemoNameAndDescProviderInterface;

typedef GType (*PFN_NEMO_NAME_AND_DESC_PROVIDER_GET_TYPE)(void);
extern PFN_NEMO_NAME_AND_DESC_PROVIDER_GET_TYPE pfn_nemo_name_and_desc_provider_get_type;

#define NEMO_TYPE_NAME_AND_DESC_PROVIDER		(pfn_nemo_name_and_desc_provider_get_type ())
#define NEMO_NAME_AND_DESC_PROVIDER(obj)		(G_TYPE_CHECK_INSTANCE_CAST((obj), NEMO_TYPE_NAME_AND_DESC_PROVIDER, NemoNameAndDescProvider))
#define NEMO_IS_NAME_AND_DESC_PROVIDER(obj)		(G_TYPE_CHECK_INSTANCE_TYPE((obj), NEMO_TYPE_NAME_AND_DESC_PROVIDER))
#define NEMO_NAME_AND_DESC_PROVIDER_GET_IFACE(obj)	(G_TYPE_INSTANCE_GET_INTERFACE((obj),  NEMO_TYPE_NAME_AND_DESC_PROVIDER, NemoNameAndDescProviderInterface))
#endif /* HAVE_NEMO_INTERFACE */

/** rom-properties functions **/

#ifdef HAVE_NEMO_INTERFACES
/**
 * Initialize Nemo-specific function pointers.
 * @param libextension_so dlopen()'d handle to libcaja-extension.so.
 */
void rp_nemo_init(void *libextension_so);
#endif /* HAVE_NEMO_INTERFACES */

/**
 * Add extra fork-specific interfaces.
 * Call this function from rp_*_provider_register_type_ext().
 * @param g_module GTypeModule
 * @param instance_type Instance type
 */
void
rp_nautilus_extra_interfaces_add(GTypeModule *g_module, GType instance_type);

G_END_DECLS
