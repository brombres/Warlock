package com.developer.warlockapp;

import android.util.Log;
import java.util.*;
import org.json.*;

public class Message
{
  public String   id;
  public JSONData data;

  public Message( String id )
  {
    this.id = id;
    data = new JSONData();
    data.set( "id", id );
  }

  public Message( String id, JSONData data )
  {
    this.id = id;
    this.data = new JSONData( data.toJSONObject().toString() );
    this.data.set( "id", id );
  }

  public Message( JSONData data )
  {
    this.data = data;
    id = getString( "id" );
  }

  public Message( JSONObject data )
  {
    this.data = new JSONData( data );
    id = getString( "id" );
  }

  public Message createReply()
  {
    return new Message( getString("response_id") );
  }

  public Message createReply( JSONData data )
  {
    return new Message( getString("response_id"), data );
  }

  public int getInt( String name )
  {
    return data.getInt( name );
  }

  public boolean getLogical( String name )
  {
    return data.getLogical( name );
  }

  public double getReal( String name )
  {
    return data.getReal( name );
  }

  public String getString( String name )
  {
    return data.getString( name );
  }

  public JSONData getTable( String name )
  {
    return data.getTable( name );
  }

  public void sendReply()
  {
    new Message( getString("response_id") ).send();
  }

  public void sendReply( JSONData data )
  {
    new Message( getString("response_id"), data ).send();
  }

  public void send()
  {
    if (getString("id") != null)
    {
      MainActivity.instance.sendMessage( this );
    }
  }

  public Message set( String name, boolean value )
  {
    data.set( name, value );
    return this;
  }

  public Message set( String name, double value )
  {
    data.set( name, value );
    return this;
  }

  public Message set( String name, int value )
  {
    data.set( name, value );
    return this;
  }

  public Message set( String name, JSONData value )
  {
    data.set( name, value );
    return this;
  }

  public Message set( String name, String value )
  {
    data.set( name, value );
    return this;
  }

  public boolean stringEquals( String key, String other )
  {
    return data.stringEquals( key, other );
  }

  public JSONObject toJSONObject()
  {
    return data.toJSONObject();
  }

  public String toString()
  {
    return data.toString();
  }
}
