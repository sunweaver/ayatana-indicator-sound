/*
This service primarily controls PulseAudio and is driven by the sound indicator menu on the panel.
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
using Gee;

[DBus (name = "org.mpris.MediaPlayer.Player")]
public interface MprisPlayer : Object {
	
	public struct Status { 
    public int32 Playback_State;
    public double Playback_Rate;
    public bool Repeat_State;
    public bool Shuffle_State;
		public bool Endless_State;
	}
	
	public abstract HashTable<string, Value?> Metadata{owned get;}
	public abstract double Volume{get;}
	public abstract int32 Capabilities{get;}
	public abstract int32 Position{get;}
	
	public abstract void SetPosition(string prop, int32 pos) throws DBus.Error;
	public abstract void PlayPause() throws DBus.Error;
	public abstract void Pause() throws DBus.Error;
	public abstract void Next() throws DBus.Error;
	public abstract void Previous() throws DBus.Error;

	public abstract signal void StatusChanged(Status update);
	public abstract signal void TrackChanged(HashTable<string,Value?> Metadata);
}

/*
 This class will entirely replace mpris-controller.vala hence why there is no
 point in trying to get encorporate both into the same object model. 
 */
public class Mpris2Controller : GLib.Object
{		
	private DBus.Connection connection;
	public dynamic DBus.Object mpris2_root {get; construct;}		
	public MprisPlayer mpris2_player {get; construct;}		
	public PlayerController owner {get; construct;}	
	
	public Mpris2Controller(PlayerController ctrl)
	{
		Object(owner: ctrl);
		this.mpris2_root = null;
		this.mpris2_player = null;
	}
	
	construct{
    try {
			debug("Going to try and create an mpris 2 controller");			
      this.connection = DBus.Bus.get (DBus.BusType.SESSION);
    } catch (Error e) {
      error("Problems connecting to the session bus - %s", e.message);
    }

		try {
			this.mpris2_root = this.connection.get_object ("org.mpris.mediaplayers.".concat(this.owner.name.down()),
				                                            "/org/mpris/MediaPlayer", 
				                                            "org.mpris.MediaPlayer");				
			this.mpris2_player = (MprisPlayer)this.connection.get_object ("org.mpris.mediaplayers.".concat(this.owner.name.down()) ,
				                                              							"/org/mpris/MediaPlayer/Player", 
				                                                            "org.mpris.MediaPlayer.Player");			
		}
		catch(Error e){
			error("Problems connecting to  
		}
	}

	public bool was_successfull(){
		if(this.mpris2_root == null ||
		   this.mpris2_player == null)
		{
			return false;
		}
		return true;
	}
	
	public void initial_update()
	{
		this.mpris2_player.TrackChanged += onTrackChanged;	
    this.mpris2_player.StatusChanged += onStatusChanged;
		
		bool r  =  (bool)this.mpris2_player.Status.Shuffle_State;
		int32 p  =  (int32)this.mpris2_player.Status.Playback_State;

		debug("initial update - play state %i", p);
		debug("initial update - shuffle state %s", r.to_string());
		
		(this.owner.custom_items[PlayerController.widget_order.TRANSPORT] as TransportMenuitem).change_play_state(p);
		this.owner.custom_items[PlayerController.widget_order.METADATA].update(this.mpris2_player.Metadata,
			                          MetadataMenuitem.attributes_format());
		this.owner.custom_items[PlayerController.widget_order.SCRUB].update(this.mpris2_player.Metadata,
			                      ScrubMenuitem.attributes_format());		
		ScrubMenuitem scrub = this.owner.custom_items[PlayerController.widget_order.SCRUB] as ScrubMenuitem;
		scrub.update_position(this.mpris2_player.Position);
		
	}

	public void transport_event(TransportMenuitem.action command)
	{		
		debug("transport_event input = %i", (int)command);
		if(command == TransportMenuitem.action.PLAY_PAUSE){
			debug("transport_event PLAY_PAUSE");
			this.mpris2_player.PlayPause();							
		}
		else if(command == TransportMenuitem.action.PREVIOUS){
			this.mpris2_player.Previous();
		}
		else if(command == TransportMenuitem.action.NEXT){
			this.mpris2_player.Next();
		}		
	}

	public void set_position(double position)
	{		
		debug("Set position with pos (0-100) %f", position);
		HashTable<string, Value?> data = this.mpris2_player.Metadata;
		Value? time_value = data.lookup("time");
		if(time_value == null){
			warning("Can't fetch the duration of the track therefore cant set the position");
			return;
		}
		uint32 total_time = time_value.get_uint();
		debug("total time of track = %i", (int)total_time);				
		double new_time_position = total_time * position/100.0;
		debug("new position = %f", (new_time_position * 1000));		

		Value? v = this.mpris2_player.Metadata.lookup("trackid");
		if(v != null){
			if(v.holds (typeof (int))){
				debug("the trackid = %i", v.get_int());			
			}
			else if(v.holds (typeof (string))){
				debug("the trackid = %s", v.get_string());
			}
		}
			        
		//this.mpris2_player.SetPosition((int32)(new_time_position));
		ScrubMenuitem scrub = this.owner.custom_items[PlayerController.widget_order.SCRUB] as ScrubMenuitem;
		scrub.update_position(this.mpris2_player.Position);				
	}
	
	public bool connected()
	{
		return (this.mpris2_player != null);
	}
	
	private void onStatusChanged(MprisPlayer.Status st)
  {
		debug("onStatusChange - play state %i", st.Playback_State);
		HashTable<string, Value?> ht = new HashTable<string, Value?>(str_hash, str_equal);
		Value v = Value(typeof(int));
		v.set_int(st.Playback_State);
		ht.insert("state", v); 
		this.owner.custom_items[PlayerController.widget_order.TRANSPORT].update(ht, TransportMenuitem.attributes_format());
		this.owner.custom_items[PlayerController.widget_order.SCRUB].update(ht, ScrubMenuitem.attributes_format());		
	}
	
	private void onTrackChanged(HashTable<string,Value?> ht)
	{
		this.owner.custom_items[PlayerController.widget_order.METADATA].reset(MetadataMenuitem.attributes_format());
		this.owner.custom_items[PlayerController.widget_order.SCRUB].reset(ScrubMenuitem.attributes_format());
		this.owner.custom_items[PlayerController.widget_order.METADATA].update(ht,
		                            MetadataMenuitem.attributes_format());
		debug("about to update the duration on the scrub bar");
		Value? v = ht.lookup("time");
		if(v != null)
		{
			debug("with the duration of %i", (int)v.get_uint()); 
			debug("with Position of %i", this.mpris2_player.Position); 
		}
		this.owner.custom_items[PlayerController.widget_order.SCRUB].update(ht,
		                        ScrubMenuitem.attributes_format());		
		ScrubMenuitem scrub = this.owner.custom_items[PlayerController.widget_order.SCRUB] as ScrubMenuitem;
		scrub.update_position(this.mpris2_player.Position);
	}
	
}



