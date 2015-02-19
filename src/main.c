/*
 * Copyright © 2015 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <locale.h>
#include <libnotify/notify.h>

#include "indicator-sound-service.h"
#include "config.h"

static gboolean
sigterm_handler (gpointer data)
{
	g_debug("Got SIGTERM");
	g_main_loop_quit((GMainLoop *)data);
	return G_SOURCE_REMOVE;
}

static void
name_lost (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
	g_debug("Name lost");
	g_main_loop_quit((GMainLoop *)user_data);
}

int
main (int argc, char ** argv) {
	GMainLoop * loop = NULL;
	IndicatorSoundService* service = NULL;
	GDBusConnection * bus = NULL;

	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	setlocale (LC_ALL, "");
	bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);

	/* Grab DBus */
	GError * error = NULL;
	bus = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
	if (error != NULL) {
		g_error("Unable to get session bus: %s", error->message);
		g_error_free(error);
		return -1;
	}

	/* Build Mainloop */
	loop = g_main_loop_new(NULL, FALSE);

	g_unix_signal_add(SIGTERM, sigterm_handler, loop); 

	/* Initialize libnotify */
	notify_init ("indicator-sound");

	MediaPlayerList * playerlist = NULL;
	AccountsServiceUser * accounts = NULL;

	if (g_strcmp0("lightdm", g_get_user_name()) == 0) {
		playerlist = MEDIA_PLAYER_LIST(media_player_list_greeter_new());
	} else {
		playerlist = MEDIA_PLAYER_LIST(media_player_list_mpris_new());
		accounts = accounts_service_user_new();
	}

	VolumeControlPulse * volume = volume_control_pulse_new();

	service = indicator_sound_service_new (playerlist, volume, accounts);

	g_bus_own_name_on_connection(bus,
		"com.canonical.indicator.sound",
		G_BUS_NAME_OWNER_FLAGS_NONE,
		NULL, /* acquired */
		name_lost,
		loop,
		NULL);

	g_main_loop_run(loop);

	g_clear_object(&playerlist);
	g_clear_object(&accounts);
	g_clear_object(&service);
	g_clear_object(&bus);

	return 0;
}

