/* music-player-bridge.c generated by valac 0.12.1, the Vala compiler
 * generated from music-player-bridge.vala, do not modify */

/*
Copyright 2010 Canonical Ltd.

Authors:
    Conor Curran <conor.curran@canonical.com>

This program is free software: you can redistribute it and/or modify it 
under the terms of the GNU General Public License version 3, as published 
by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranties of 
MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR 
PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along 
with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <glib.h>
#include <glib-object.h>
#include <libdbusmenu-glib/client.h>
#include <libdbusmenu-glib/dbusmenu-glib.h>
#include <libdbusmenu-glib/enum-types.h>
#include <libdbusmenu-glib/menuitem-proxy.h>
#include <libdbusmenu-glib/menuitem.h>
#include <libdbusmenu-glib/server.h>
#include <libdbusmenu-glib/types.h>
#include <gee.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>
#include <gio/gdesktopappinfo.h>


#define TYPE_MUSIC_PLAYER_BRIDGE (music_player_bridge_get_type ())
#define MUSIC_PLAYER_BRIDGE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MUSIC_PLAYER_BRIDGE, MusicPlayerBridge))
#define MUSIC_PLAYER_BRIDGE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MUSIC_PLAYER_BRIDGE, MusicPlayerBridgeClass))
#define IS_MUSIC_PLAYER_BRIDGE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MUSIC_PLAYER_BRIDGE))
#define IS_MUSIC_PLAYER_BRIDGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MUSIC_PLAYER_BRIDGE))
#define MUSIC_PLAYER_BRIDGE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MUSIC_PLAYER_BRIDGE, MusicPlayerBridgeClass))

typedef struct _MusicPlayerBridge MusicPlayerBridge;
typedef struct _MusicPlayerBridgeClass MusicPlayerBridgeClass;
typedef struct _MusicPlayerBridgePrivate MusicPlayerBridgePrivate;

#define TYPE_SETTINGS_MANAGER (settings_manager_get_type ())
#define SETTINGS_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SETTINGS_MANAGER, SettingsManager))
#define SETTINGS_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SETTINGS_MANAGER, SettingsManagerClass))
#define IS_SETTINGS_MANAGER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SETTINGS_MANAGER))
#define IS_SETTINGS_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SETTINGS_MANAGER))
#define SETTINGS_MANAGER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SETTINGS_MANAGER, SettingsManagerClass))

typedef struct _SettingsManager SettingsManager;
typedef struct _SettingsManagerClass SettingsManagerClass;

#define TYPE_PLAYER_CONTROLLER (player_controller_get_type ())
#define PLAYER_CONTROLLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PLAYER_CONTROLLER, PlayerController))
#define PLAYER_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PLAYER_CONTROLLER, PlayerControllerClass))
#define IS_PLAYER_CONTROLLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PLAYER_CONTROLLER))
#define IS_PLAYER_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PLAYER_CONTROLLER))
#define PLAYER_CONTROLLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PLAYER_CONTROLLER, PlayerControllerClass))

typedef struct _PlayerController PlayerController;
typedef struct _PlayerControllerClass PlayerControllerClass;

#define TYPE_MPRIS2_WATCHER (mpris2_watcher_get_type ())
#define MPRIS2_WATCHER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MPRIS2_WATCHER, Mpris2Watcher))
#define MPRIS2_WATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MPRIS2_WATCHER, Mpris2WatcherClass))
#define IS_MPRIS2_WATCHER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MPRIS2_WATCHER))
#define IS_MPRIS2_WATCHER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MPRIS2_WATCHER))
#define MPRIS2_WATCHER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MPRIS2_WATCHER, Mpris2WatcherClass))

typedef struct _Mpris2Watcher Mpris2Watcher;
typedef struct _Mpris2WatcherClass Mpris2WatcherClass;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

#define PLAYER_CONTROLLER_TYPE_STATE (player_controller_state_get_type ())
typedef struct _PlayerControllerPrivate PlayerControllerPrivate;

#define TYPE_PLAYER_ITEM (player_item_get_type ())
#define PLAYER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_PLAYER_ITEM, PlayerItem))
#define PLAYER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_PLAYER_ITEM, PlayerItemClass))
#define IS_PLAYER_ITEM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_PLAYER_ITEM))
#define IS_PLAYER_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_PLAYER_ITEM))
#define PLAYER_ITEM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_PLAYER_ITEM, PlayerItemClass))

typedef struct _PlayerItem PlayerItem;
typedef struct _PlayerItemClass PlayerItemClass;

#define TYPE_MPRIS2_CONTROLLER (mpris2_controller_get_type ())
#define MPRIS2_CONTROLLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_MPRIS2_CONTROLLER, Mpris2Controller))
#define MPRIS2_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MPRIS2_CONTROLLER, Mpris2ControllerClass))
#define IS_MPRIS2_CONTROLLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_MPRIS2_CONTROLLER))
#define IS_MPRIS2_CONTROLLER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MPRIS2_CONTROLLER))
#define MPRIS2_CONTROLLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_MPRIS2_CONTROLLER, Mpris2ControllerClass))

typedef struct _Mpris2Controller Mpris2Controller;
typedef struct _Mpris2ControllerClass Mpris2ControllerClass;
#define _g_key_file_free0(var) ((var == NULL) ? NULL : (var = (g_key_file_free (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

struct _MusicPlayerBridge {
	GObject parent_instance;
	MusicPlayerBridgePrivate * priv;
};

struct _MusicPlayerBridgeClass {
	GObjectClass parent_class;
};

struct _MusicPlayerBridgePrivate {
	SettingsManager* settings_manager;
	DbusmenuMenuitem* root_menu;
	GeeHashMap* registered_clients;
	Mpris2Watcher* watcher;
};

typedef enum  {
	PLAYER_CONTROLLER_STATE_OFFLINE,
	PLAYER_CONTROLLER_STATE_INSTANTIATING,
	PLAYER_CONTROLLER_STATE_READY,
	PLAYER_CONTROLLER_STATE_CONNECTED,
	PLAYER_CONTROLLER_STATE_DISCONNECTED
} PlayerControllerstate;

struct _PlayerController {
	GObject parent_instance;
	PlayerControllerPrivate * priv;
	gint current_state;
	DbusmenuMenuitem* root_menu;
	GeeArrayList* custom_items;
	Mpris2Controller* mpris_bridge;
	gboolean* use_playlists;
};

struct _PlayerControllerClass {
	GObjectClass parent_class;
};


static gpointer music_player_bridge_parent_class = NULL;

GType music_player_bridge_get_type (void) G_GNUC_CONST;
GType settings_manager_get_type (void) G_GNUC_CONST;
GType player_controller_get_type (void) G_GNUC_CONST;
GType mpris2_watcher_get_type (void) G_GNUC_CONST;
#define MUSIC_PLAYER_BRIDGE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_MUSIC_PLAYER_BRIDGE, MusicPlayerBridgePrivate))
enum  {
	MUSIC_PLAYER_BRIDGE_DUMMY_PROPERTY
};
#define MUSIC_PLAYER_BRIDGE_DEVICE_ITEMS_COUNT 3
MusicPlayerBridge* music_player_bridge_new (void);
MusicPlayerBridge* music_player_bridge_construct (GType object_type);
static void music_player_bridge_on_blacklist_update (MusicPlayerBridge* self, gchar** blacklist, int blacklist_length1);
static gchar* music_player_bridge_determine_key (gchar* desktop_or_interface);
void player_controller_remove_from_menu (PlayerController* self);
void mpris2_watcher_check_for_active_clients (Mpris2Watcher* self, GAsyncReadyCallback _callback_, gpointer _user_data_);
void mpris2_watcher_check_for_active_clients_finish (Mpris2Watcher* self, GAsyncResult* _res_);
static void music_player_bridge_try_to_add_inactive_familiar_clients (MusicPlayerBridge* self);
GeeArrayList* settings_manager_fetch_interested (SettingsManager* self);
static GAppInfo* music_player_bridge_create_app_info (const gchar* desktop);
static gchar* music_player_bridge_fetch_icon_name (const gchar* desktop);
static gint music_player_bridge_calculate_menu_position (MusicPlayerBridge* self);
GType player_controller_state_get_type (void) G_GNUC_CONST;
PlayerController* player_controller_new (DbusmenuMenuitem* root, GAppInfo* app, const gchar* dbus_name, const gchar* icon_name, gint offset, gboolean* use_playlists, PlayerControllerstate initial_state);
PlayerController* player_controller_construct (GType object_type, DbusmenuMenuitem* root, GAppInfo* app, const gchar* dbus_name, const gchar* icon_name, gint offset, gboolean* use_playlists, PlayerControllerstate initial_state);
#define PLAYER_CONTROLLER_WIDGET_QUANTITY 4
void music_player_bridge_client_has_become_available (MusicPlayerBridge* self, const gchar* desktop, const gchar* dbus_name, gboolean use_playlists);
gchar** settings_manager_fetch_blacklist (SettingsManager* self, int* result_length1);
static gboolean _vala_string_array_contains (gchar** stack, int stack_length, gchar* needle);
void settings_manager_add_interested (SettingsManager* self, const gchar* app_desktop_name);
static gboolean* _bool_dup (gboolean* self);
GType player_item_get_type (void) G_GNUC_CONST;
GType mpris2_controller_get_type (void) G_GNUC_CONST;
void player_controller_update_state (PlayerController* self, PlayerControllerstate new_state);
void player_controller_activate (PlayerController* self, const gchar* dbus_name);
void music_player_bridge_client_has_vanished (MusicPlayerBridge* self, const gchar* mpris_root_interface);
void player_controller_hibernate (PlayerController* self);
void music_player_bridge_set_root_menu_item (MusicPlayerBridge* self, DbusmenuMenuitem* menu);
Mpris2Watcher* mpris2_watcher_new (void);
Mpris2Watcher* mpris2_watcher_construct (GType object_type);
static void _music_player_bridge_client_has_become_available_mpris2_watcher_client_appeared (Mpris2Watcher* _sender, const gchar* desktop_file_name, const gchar* dbus_name, gboolean use_playlists, gpointer self);
static void _music_player_bridge_client_has_vanished_mpris2_watcher_client_disappeared (Mpris2Watcher* _sender, const gchar* dbus_name, gpointer self);
void music_player_bridge_enable_player_specific_items_for_client (MusicPlayerBridge* self, const gchar* object_path, const gchar* desktop_id);
void player_controller_enable_player_specific_items (PlayerController* self, const gchar* object_path);
void music_player_bridge_enable_track_specific_items_for_client (MusicPlayerBridge* self, const gchar* object_path, const gchar* desktop_id);
void player_controller_enable_track_specific_items (PlayerController* self, const gchar* object_path);
static GObject * music_player_bridge_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
SettingsManager* settings_manager_new (void);
SettingsManager* settings_manager_construct (GType object_type);
static void _music_player_bridge_on_blacklist_update_settings_manager_blacklist_updates (SettingsManager* _sender, gchar** new_blacklist, int new_blacklist_length1, gpointer self);
static void music_player_bridge_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);


MusicPlayerBridge* music_player_bridge_construct (GType object_type) {
	MusicPlayerBridge * self = NULL;
	self = (MusicPlayerBridge*) g_object_new (object_type, NULL);
	return self;
}


MusicPlayerBridge* music_player_bridge_new (void) {
	return music_player_bridge_construct (TYPE_MUSIC_PLAYER_BRIDGE);
}


static void music_player_bridge_on_blacklist_update (MusicPlayerBridge* self, gchar** blacklist, int blacklist_length1) {
	g_return_if_fail (self != NULL);
	g_debug ("music-player-bridge.vala:45: some blacklist update");
	{
		gchar** s_collection;
		int s_collection_length1;
		int s_it;
		s_collection = blacklist;
		s_collection_length1 = blacklist_length1;
		for (s_it = 0; s_it < blacklist_length1; s_it = s_it + 1) {
			gchar* _tmp0_;
			gchar* s;
			_tmp0_ = g_strdup (s_collection[s_it]);
			s = _tmp0_;
			{
				gchar* _tmp1_;
				gchar* _tmp2_ = NULL;
				gchar* key;
				gboolean _tmp3_;
				_tmp1_ = g_strdup (s);
				_tmp2_ = music_player_bridge_determine_key (_tmp1_);
				key = _tmp2_;
				_tmp3_ = gee_abstract_map_has_key ((GeeAbstractMap*) self->priv->registered_clients, key);
				if (_tmp3_) {
					gpointer _tmp4_ = NULL;
					PlayerController* _tmp5_;
					g_debug ("music-player-bridge.vala:50: Apparently %s is now blacklisted - remove" \
" thy self", key);
					_tmp4_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, key);
					_tmp5_ = (PlayerController*) _tmp4_;
					player_controller_remove_from_menu (_tmp5_);
					_g_object_unref0 (_tmp5_);
					gee_abstract_map_unset ((GeeAbstractMap*) self->priv->registered_clients, key, NULL);
				}
				_g_free0 (key);
				_g_free0 (s);
			}
		}
	}
	mpris2_watcher_check_for_active_clients (self->priv->watcher, NULL, NULL);
}


static void music_player_bridge_try_to_add_inactive_familiar_clients (MusicPlayerBridge* self) {
	g_return_if_fail (self != NULL);
	{
		GeeArrayList* _tmp0_ = NULL;
		GeeArrayList* _desktop_list;
		gint _tmp1_;
		gint _desktop_size;
		gint _desktop_index;
		_tmp0_ = settings_manager_fetch_interested (self->priv->settings_manager);
		_desktop_list = _tmp0_;
		_tmp1_ = gee_collection_get_size ((GeeCollection*) _desktop_list);
		_desktop_size = _tmp1_;
		_desktop_index = -1;
		while (TRUE) {
			gpointer _tmp2_ = NULL;
			gchar* desktop;
			gchar* _tmp3_ = NULL;
			gchar* _tmp4_;
			GAppInfo* _tmp5_ = NULL;
			GAppInfo* _tmp6_;
			GAppInfo* app_info;
			gchar* _tmp7_;
			gchar* _tmp8_ = NULL;
			gchar* mpris_key;
			gchar* _tmp9_ = NULL;
			gchar* _tmp10_;
			gint _tmp11_;
			PlayerController* _tmp12_ = NULL;
			PlayerController* _tmp13_;
			PlayerController* ctrl;
			_desktop_index = _desktop_index + 1;
			if (!(_desktop_index < _desktop_size)) {
				break;
			}
			_tmp2_ = gee_abstract_list_get ((GeeAbstractList*) _desktop_list, _desktop_index);
			desktop = (gchar*) _tmp2_;
			g_debug ("music-player-bridge.vala:62: interested client found : %s", desktop);
			_tmp3_ = g_strconcat (desktop, ".desktop", NULL);
			_tmp4_ = _tmp3_;
			_tmp5_ = music_player_bridge_create_app_info (_tmp4_);
			_tmp6_ = _tmp5_;
			_g_free0 (_tmp4_);
			app_info = _tmp6_;
			if (app_info == NULL) {
				g_warning ("music-player-bridge.vala:65: Could not create app_info for path %s \n" \
" Getting out of here ", desktop);
				_g_object_unref0 (app_info);
				_g_free0 (desktop);
				continue;
			}
			_tmp7_ = g_strdup (desktop);
			_tmp8_ = music_player_bridge_determine_key (_tmp7_);
			mpris_key = _tmp8_;
			_tmp9_ = music_player_bridge_fetch_icon_name (desktop);
			_tmp10_ = _tmp9_;
			_tmp11_ = music_player_bridge_calculate_menu_position (self);
			_tmp12_ = player_controller_new (self->priv->root_menu, app_info, NULL, _tmp10_, _tmp11_, NULL, PLAYER_CONTROLLER_STATE_OFFLINE);
			_tmp13_ = _tmp12_;
			_g_free0 (_tmp10_);
			ctrl = _tmp13_;
			gee_abstract_map_set ((GeeAbstractMap*) self->priv->registered_clients, mpris_key, ctrl);
			_g_object_unref0 (ctrl);
			_g_free0 (mpris_key);
			_g_object_unref0 (app_info);
			_g_free0 (desktop);
		}
		_g_object_unref0 (_desktop_list);
	}
}


static gint music_player_bridge_calculate_menu_position (MusicPlayerBridge* self) {
	gint result = 0;
	gint _tmp0_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = gee_map_get_size ((GeeMap*) self->priv->registered_clients);
	if (_tmp0_ == 0) {
		result = MUSIC_PLAYER_BRIDGE_DEVICE_ITEMS_COUNT;
		return result;
	} else {
		gint _tmp1_;
		_tmp1_ = gee_map_get_size ((GeeMap*) self->priv->registered_clients);
		result = MUSIC_PLAYER_BRIDGE_DEVICE_ITEMS_COUNT + (_tmp1_ * PLAYER_CONTROLLER_WIDGET_QUANTITY);
		return result;
	}
}


static gboolean _vala_string_array_contains (gchar** stack, int stack_length, gchar* needle) {
	int i;
	for (i = 0; i < stack_length; i++) {
		if (g_strcmp0 (stack[i], needle) == 0) {
			return TRUE;
		}
	}
	return FALSE;
}


static gboolean* _bool_dup (gboolean* self) {
	gboolean* dup;
	dup = g_new0 (gboolean, 1);
	memcpy (dup, self, sizeof (gboolean));
	return dup;
}


static gpointer __bool_dup0 (gpointer self) {
	return self ? _bool_dup (self) : NULL;
}


void music_player_bridge_client_has_become_available (MusicPlayerBridge* self, const gchar* desktop, const gchar* dbus_name, gboolean use_playlists) {
	gboolean _tmp0_ = FALSE;
	gint _tmp1_;
	gchar** _tmp2_ = NULL;
	gchar** _tmp3_;
	gint _tmp3__length1;
	gboolean _tmp4_;
	gchar* _tmp5_ = NULL;
	gchar* _tmp6_;
	GAppInfo* _tmp7_ = NULL;
	GAppInfo* _tmp8_;
	GAppInfo* app_info;
	gchar* _tmp9_;
	gchar* _tmp10_ = NULL;
	gchar* mpris_key;
	gboolean _tmp11_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (desktop != NULL);
	g_return_if_fail (dbus_name != NULL);
	if (desktop == NULL) {
		_tmp0_ = TRUE;
	} else {
		_tmp0_ = g_strcmp0 (desktop, "") == 0;
	}
	if (_tmp0_) {
		g_warning ("music-player-bridge.vala:96: Client %s attempting to register without " \
"desktop entry being set on the mpris root", dbus_name);
		return;
	}
	_tmp2_ = settings_manager_fetch_blacklist (self->priv->settings_manager, &_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp3__length1 = _tmp1_;
	_tmp4_ = _vala_string_array_contains (_tmp3_, _tmp1_, desktop);
	_tmp3_ = (_vala_array_free (_tmp3_, _tmp3__length1, (GDestroyNotify) g_free), NULL);
	if (_tmp4_) {
		g_debug ("music-player-bridge.vala:101: Client %s attempting to register but I'm" \
" afraid it is blacklisted", desktop);
		return;
	}
	g_debug ("music-player-bridge.vala:106: client_has_become_available %s", desktop);
	_tmp5_ = g_strconcat (desktop, ".desktop", NULL);
	_tmp6_ = _tmp5_;
	_tmp7_ = music_player_bridge_create_app_info (_tmp6_);
	_tmp8_ = _tmp7_;
	_g_free0 (_tmp6_);
	app_info = _tmp8_;
	if (app_info == NULL) {
		g_warning ("music-player-bridge.vala:109: Could not create app_info for path %s \n" \
" Getting out of here ", desktop);
		_g_object_unref0 (app_info);
		return;
	}
	_tmp9_ = g_strdup (desktop);
	_tmp10_ = music_player_bridge_determine_key (_tmp9_);
	mpris_key = _tmp10_;
	_tmp11_ = gee_abstract_map_has_key ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
	if (_tmp11_ == FALSE) {
		gchar* _tmp12_ = NULL;
		gchar* _tmp13_;
		gint _tmp14_;
		PlayerController* _tmp15_ = NULL;
		PlayerController* _tmp16_;
		PlayerController* ctrl;
		g_debug ("music-player-bridge.vala:117: New client has registered that we have n" \
"ot seen before: %s", dbus_name);
		_tmp12_ = music_player_bridge_fetch_icon_name (desktop);
		_tmp13_ = _tmp12_;
		_tmp14_ = music_player_bridge_calculate_menu_position (self);
		_tmp15_ = player_controller_new (self->priv->root_menu, app_info, dbus_name, _tmp13_, _tmp14_, &use_playlists, PLAYER_CONTROLLER_STATE_READY);
		_tmp16_ = _tmp15_;
		_g_free0 (_tmp13_);
		ctrl = _tmp16_;
		gee_abstract_map_set ((GeeAbstractMap*) self->priv->registered_clients, mpris_key, ctrl);
		g_debug ("music-player-bridge.vala:126: Have not seen this %s before, new contro" \
"ller created.", desktop);
		settings_manager_add_interested (self->priv->settings_manager, desktop);
		g_debug ("music-player-bridge.vala:128: application added to the interested list");
		_g_object_unref0 (ctrl);
	} else {
		gpointer _tmp17_ = NULL;
		PlayerController* _tmp18_;
		gboolean* _tmp19_;
		gpointer _tmp20_ = NULL;
		PlayerController* _tmp21_;
		gpointer _tmp22_ = NULL;
		PlayerController* _tmp23_;
		_tmp17_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
		_tmp18_ = (PlayerController*) _tmp17_;
		_tmp19_ = __bool_dup0 (&use_playlists);
		_g_free0 (_tmp18_->use_playlists);
		_tmp18_->use_playlists = _tmp19_;
		_g_object_unref0 (_tmp18_);
		_tmp20_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
		_tmp21_ = (PlayerController*) _tmp20_;
		player_controller_update_state (_tmp21_, PLAYER_CONTROLLER_STATE_READY);
		_g_object_unref0 (_tmp21_);
		_tmp22_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
		_tmp23_ = (PlayerController*) _tmp22_;
		player_controller_activate (_tmp23_, dbus_name);
		_g_object_unref0 (_tmp23_);
		g_debug ("music-player-bridge.vala:134: Application has already registered - awa" \
"ken the hibernation: %s \n", dbus_name);
	}
	_g_free0 (mpris_key);
	_g_object_unref0 (app_info);
}


void music_player_bridge_client_has_vanished (MusicPlayerBridge* self, const gchar* mpris_root_interface) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (mpris_root_interface != NULL);
	g_debug ("music-player-bridge.vala:140: MusicPlayerBridge -> client with dbus in" \
"terface %s has vanished", mpris_root_interface);
	if (self->priv->root_menu != NULL) {
		gchar* _tmp0_;
		gchar* _tmp1_ = NULL;
		gchar* mpris_key;
		gboolean _tmp2_ = FALSE;
		g_debug ("music-player-bridge.vala:143: attempt to remove %s", mpris_root_interface);
		_tmp0_ = g_strdup (mpris_root_interface);
		_tmp1_ = music_player_bridge_determine_key (_tmp0_);
		mpris_key = _tmp1_;
		if (mpris_key != NULL) {
			gboolean _tmp3_;
			_tmp3_ = gee_abstract_map_has_key ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
			_tmp2_ = _tmp3_;
		} else {
			_tmp2_ = FALSE;
		}
		if (_tmp2_) {
			gpointer _tmp4_ = NULL;
			PlayerController* _tmp5_;
			_tmp4_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
			_tmp5_ = (PlayerController*) _tmp4_;
			player_controller_hibernate (_tmp5_);
			_g_object_unref0 (_tmp5_);
			g_debug ("music-player-bridge.vala:147: Successively offlined client %s", mpris_key);
		}
		_g_free0 (mpris_key);
	}
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _music_player_bridge_client_has_become_available_mpris2_watcher_client_appeared (Mpris2Watcher* _sender, const gchar* desktop_file_name, const gchar* dbus_name, gboolean use_playlists, gpointer self) {
	music_player_bridge_client_has_become_available (self, desktop_file_name, dbus_name, use_playlists);
}


static void _music_player_bridge_client_has_vanished_mpris2_watcher_client_disappeared (Mpris2Watcher* _sender, const gchar* dbus_name, gpointer self) {
	music_player_bridge_client_has_vanished (self, dbus_name);
}


void music_player_bridge_set_root_menu_item (MusicPlayerBridge* self, DbusmenuMenuitem* menu) {
	DbusmenuMenuitem* _tmp0_;
	Mpris2Watcher* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (menu != NULL);
	_tmp0_ = _g_object_ref0 (menu);
	_g_object_unref0 (self->priv->root_menu);
	self->priv->root_menu = _tmp0_;
	music_player_bridge_try_to_add_inactive_familiar_clients (self);
	_tmp1_ = mpris2_watcher_new ();
	_g_object_unref0 (self->priv->watcher);
	self->priv->watcher = _tmp1_;
	g_signal_connect_object (self->priv->watcher, "client-appeared", (GCallback) _music_player_bridge_client_has_become_available_mpris2_watcher_client_appeared, self, 0);
	g_signal_connect_object (self->priv->watcher, "client-disappeared", (GCallback) _music_player_bridge_client_has_vanished_mpris2_watcher_client_disappeared, self, 0);
}


void music_player_bridge_enable_player_specific_items_for_client (MusicPlayerBridge* self, const gchar* object_path, const gchar* desktop_id) {
	gchar* _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* mpris_key;
	gboolean _tmp2_;
	gpointer _tmp3_ = NULL;
	PlayerController* _tmp4_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (object_path != NULL);
	g_return_if_fail (desktop_id != NULL);
	_tmp0_ = g_strdup (desktop_id);
	_tmp1_ = music_player_bridge_determine_key (_tmp0_);
	mpris_key = _tmp1_;
	_tmp2_ = gee_abstract_map_has_key ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
	if (_tmp2_ == FALSE) {
		g_warning ("music-player-bridge.vala:166: we don't have a client with desktop id %" \
"s registered", desktop_id);
		_g_free0 (mpris_key);
		return;
	}
	_tmp3_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
	_tmp4_ = (PlayerController*) _tmp3_;
	player_controller_enable_player_specific_items (_tmp4_, object_path);
	_g_object_unref0 (_tmp4_);
	_g_free0 (mpris_key);
}


void music_player_bridge_enable_track_specific_items_for_client (MusicPlayerBridge* self, const gchar* object_path, const gchar* desktop_id) {
	gchar* _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* mpris_key;
	gboolean _tmp2_;
	gpointer _tmp3_ = NULL;
	PlayerController* _tmp4_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (object_path != NULL);
	g_return_if_fail (desktop_id != NULL);
	_tmp0_ = g_strdup (desktop_id);
	_tmp1_ = music_player_bridge_determine_key (_tmp0_);
	mpris_key = _tmp1_;
	_tmp2_ = gee_abstract_map_has_key ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
	if (_tmp2_ == FALSE) {
		g_warning ("music-player-bridge.vala:177: we don't have a client with desktop id %" \
"s registered", desktop_id);
		_g_free0 (mpris_key);
		return;
	}
	_tmp3_ = gee_abstract_map_get ((GeeAbstractMap*) self->priv->registered_clients, mpris_key);
	_tmp4_ = (PlayerController*) _tmp3_;
	player_controller_enable_track_specific_items (_tmp4_, object_path);
	_g_object_unref0 (_tmp4_);
	_g_free0 (mpris_key);
}


static GAppInfo* music_player_bridge_create_app_info (const gchar* desktop) {
	GAppInfo* result = NULL;
	GDesktopAppInfo* _tmp0_ = NULL;
	GDesktopAppInfo* info;
	gboolean _tmp1_ = FALSE;
	GDesktopAppInfo* _tmp2_;
	GAppInfo* _tmp3_;
	GAppInfo* app_info;
	g_return_val_if_fail (desktop != NULL, NULL);
	_tmp0_ = g_desktop_app_info_new (desktop);
	info = _tmp0_;
	if (desktop == NULL) {
		_tmp1_ = TRUE;
	} else {
		_tmp1_ = info == NULL;
	}
	if (_tmp1_) {
		g_warning ("music-player-bridge.vala:187: Could not create a desktopappinfo instan" \
"ce from app: %s", desktop);
		result = NULL;
		_g_object_unref0 (info);
		return result;
	}
	_tmp2_ = info;
	_tmp3_ = _g_object_ref0 (G_IS_APP_INFO (_tmp2_) ? ((GAppInfo*) _tmp2_) : NULL);
	app_info = _tmp3_;
	result = app_info;
	_g_object_unref0 (info);
	return result;
}


static gchar* music_player_bridge_fetch_icon_name (const gchar* desktop) {
	gchar* result = NULL;
	gchar* _tmp0_ = NULL;
	gchar* _tmp1_;
	GDesktopAppInfo* _tmp2_ = NULL;
	GDesktopAppInfo* _tmp3_;
	GDesktopAppInfo* info;
	GKeyFile* _tmp4_ = NULL;
	GKeyFile* desktop_keyfile;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gchar* _tmp7_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (desktop != NULL, NULL);
	_tmp0_ = g_strconcat (desktop, ".desktop", NULL);
	_tmp1_ = _tmp0_;
	_tmp2_ = g_desktop_app_info_new (_tmp1_);
	_tmp3_ = _tmp2_;
	_g_free0 (_tmp1_);
	info = _tmp3_;
	_tmp4_ = g_key_file_new ();
	desktop_keyfile = _tmp4_;
	_tmp5_ = g_desktop_app_info_get_filename (info);
	g_key_file_load_from_file (desktop_keyfile, _tmp5_, G_KEY_FILE_NONE, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == G_FILE_ERROR) {
			goto __catch0_g_file_error;
		}
		if (_inner_error_->domain == G_KEY_FILE_ERROR) {
			goto __catch0_g_key_file_error;
		}
		_g_key_file_free0 (desktop_keyfile);
		_g_object_unref0 (info);
		g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	goto __finally0;
	__catch0_g_file_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		g_warning ("music-player-bridge.vala:203: Error loading keyfile - FileError");
		result = NULL;
		_g_error_free0 (_error_);
		_g_key_file_free0 (desktop_keyfile);
		_g_object_unref0 (info);
		return result;
	}
	goto __finally0;
	__catch0_g_key_file_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		g_warning ("music-player-bridge.vala:207: Error loading keyfile - KeyFileError");
		result = NULL;
		_g_error_free0 (_error_);
		_g_key_file_free0 (desktop_keyfile);
		_g_object_unref0 (info);
		return result;
	}
	__finally0:
	if (_inner_error_ != NULL) {
		_g_key_file_free0 (desktop_keyfile);
		_g_object_unref0 (info);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_tmp6_ = g_key_file_get_string (desktop_keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, &_inner_error_);
	_tmp7_ = _tmp6_;
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == G_KEY_FILE_ERROR) {
			goto __catch1_g_key_file_error;
		}
		_g_key_file_free0 (desktop_keyfile);
		_g_object_unref0 (info);
		g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	result = _tmp7_;
	_g_key_file_free0 (desktop_keyfile);
	_g_object_unref0 (info);
	return result;
	goto __finally1;
	__catch1_g_key_file_error:
	{
		GError * _error_;
		_error_ = _inner_error_;
		_inner_error_ = NULL;
		g_warning ("music-player-bridge.vala:216: Error trying to fetch the icon name from" \
" the keyfile");
		result = NULL;
		_g_error_free0 (_error_);
		_g_key_file_free0 (desktop_keyfile);
		_g_object_unref0 (info);
		return result;
	}
	__finally1:
	_g_key_file_free0 (desktop_keyfile);
	_g_object_unref0 (info);
	g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
	g_clear_error (&_inner_error_);
	return NULL;
}


static gchar* music_player_bridge_determine_key (gchar* desktop_or_interface) {
	gchar* result = NULL;
	gchar* _tmp0_;
	gchar* _result_;
	gchar** _tmp1_;
	gchar** _tmp2_ = NULL;
	gchar** tokens;
	gint tokens_length1;
	gint _tokens_size_;
	gchar** _tmp4_;
	gchar** _tmp5_ = NULL;
	gchar** temp;
	gint temp_length1;
	gint _temp_size_;
	g_return_val_if_fail (desktop_or_interface != NULL, NULL);
	_tmp0_ = g_strdup (desktop_or_interface);
	_result_ = _tmp0_;
	_tmp2_ = _tmp1_ = g_strsplit (desktop_or_interface, ".", 0);
	tokens = _tmp2_;
	tokens_length1 = _vala_array_length (_tmp1_);
	_tokens_size_ = _vala_array_length (_tmp1_);
	if (tokens_length1 > 1) {
		gchar* _tmp3_;
		_tmp3_ = g_strdup (tokens[tokens_length1 - 1]);
		_g_free0 (_result_);
		_result_ = _tmp3_;
	}
	_tmp5_ = _tmp4_ = g_strsplit (_result_, "-", 0);
	temp = _tmp5_;
	temp_length1 = _vala_array_length (_tmp4_);
	_temp_size_ = _vala_array_length (_tmp4_);
	if (temp_length1 > 1) {
		gchar* _tmp6_;
		_tmp6_ = g_strdup (temp[0]);
		_g_free0 (_result_);
		_result_ = _tmp6_;
	}
	g_debug ("music-player-bridge.vala:239: determine key result = %s", _result_);
	result = _result_;
	temp = (_vala_array_free (temp, temp_length1, (GDestroyNotify) g_free), NULL);
	tokens = (_vala_array_free (tokens, tokens_length1, (GDestroyNotify) g_free), NULL);
	_g_free0 (desktop_or_interface);
	return result;
}


static void _music_player_bridge_on_blacklist_update_settings_manager_blacklist_updates (SettingsManager* _sender, gchar** new_blacklist, int new_blacklist_length1, gpointer self) {
	music_player_bridge_on_blacklist_update (self, new_blacklist, new_blacklist_length1);
}


static GObject * music_player_bridge_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	MusicPlayerBridge * self;
	GeeHashMap* _tmp0_ = NULL;
	SettingsManager* _tmp1_ = NULL;
	parent_class = G_OBJECT_CLASS (music_player_bridge_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = MUSIC_PLAYER_BRIDGE (obj);
	_tmp0_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, TYPE_PLAYER_CONTROLLER, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL, NULL, NULL);
	_g_object_unref0 (self->priv->registered_clients);
	self->priv->registered_clients = _tmp0_;
	_tmp1_ = settings_manager_new ();
	_g_object_unref0 (self->priv->settings_manager);
	self->priv->settings_manager = _tmp1_;
	g_signal_connect_object (self->priv->settings_manager, "blacklist-updates", (GCallback) _music_player_bridge_on_blacklist_update_settings_manager_blacklist_updates, self, 0);
	return obj;
}


static void music_player_bridge_class_init (MusicPlayerBridgeClass * klass) {
	music_player_bridge_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (MusicPlayerBridgePrivate));
	G_OBJECT_CLASS (klass)->constructor = music_player_bridge_constructor;
	G_OBJECT_CLASS (klass)->finalize = music_player_bridge_finalize;
}


static void music_player_bridge_instance_init (MusicPlayerBridge * self) {
	self->priv = MUSIC_PLAYER_BRIDGE_GET_PRIVATE (self);
}


static void music_player_bridge_finalize (GObject* obj) {
	MusicPlayerBridge * self;
	self = MUSIC_PLAYER_BRIDGE (obj);
	_g_object_unref0 (self->priv->settings_manager);
	_g_object_unref0 (self->priv->root_menu);
	_g_object_unref0 (self->priv->registered_clients);
	_g_object_unref0 (self->priv->watcher);
	G_OBJECT_CLASS (music_player_bridge_parent_class)->finalize (obj);
}


GType music_player_bridge_get_type (void) {
	static volatile gsize music_player_bridge_type_id__volatile = 0;
	if (g_once_init_enter (&music_player_bridge_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (MusicPlayerBridgeClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) music_player_bridge_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (MusicPlayerBridge), 0, (GInstanceInitFunc) music_player_bridge_instance_init, NULL };
		GType music_player_bridge_type_id;
		music_player_bridge_type_id = g_type_register_static (G_TYPE_OBJECT, "MusicPlayerBridge", &g_define_type_info, 0);
		g_once_init_leave (&music_player_bridge_type_id__volatile, music_player_bridge_type_id);
	}
	return music_player_bridge_type_id__volatile;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}



