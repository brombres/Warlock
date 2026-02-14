package com.developer.appname;

import android.util.Log;
import java.util.*;
import org.json.*;

public class JSONData
{
  public JSONObject table;
  public JSONArray  list;

  //----------------------------------------------------------------------------

  static public JSONData table()
  {
    return new JSONData();
  }

  static public JSONData list()
  {
    return new JSONData( new JSONArray() );
  }

  //----------------------------------------------------------------------------

  public JSONData()
  {
    table = new JSONObject();
  }

  public JSONData( JSONObject table )
  {
    this.table = table;
  }

  public JSONData( JSONArray list )
  {
    this.list = list;
  }

  public JSONData( String json )
  {
    try
    {
      json = json.trim();
      if (json.length() >= 2)
      {
        if (json.charAt(0) == '[') this.list = new JSONArray( json );
        else                       this.table = new JSONObject( json );
      }
    }
    catch (JSONException ignore)
    {
    }
  }

  public JSONData add( boolean value )
  {
    if (list != null) list.put( value );
    return this;
  }

  public JSONData add( double value )
  {
    try
    {
      if (list != null) list.put( value );
    }
    catch (JSONException suppress) {}

    return this;
  }

  public JSONData add( int value )
  {
    if (list != null) list.put( value );
    return this;
  }

  public JSONData add( JSONData value )
  {
    if (list != null)
    {
      if (value.table != null)     list.put( value.table );
      else if (value.list != null) list.put( value.list );
    }
    return this;
  }

  public JSONData add( String value )
  {
    if (list != null) list.put( value );
    return this;
  }

  public int count()
  {
    if (list == null) return 0;
    return list.length();
  }

  public boolean getLogical( String name )
  {
    if (table == null) return false;

    try
    {
      return table.getBoolean( name );
    }
    catch (JSONException suppress)
    {
      return false;
    }
  }

  public int getInt( String name )
  {
    if (table == null) return 0;

    try
    {
      return table.getInt( name );
    }
    catch (JSONException suppress)
    {
      return 0;
    }
  }

  public JSONData getList( int index )
  {
    if (list == null) return null;

    try
    {
      JSONArray array = list.getJSONArray( index );
      if (array == null) return null;
      return new JSONData( array );
    }
    catch (JSONException suppress)
    {
      return null;
    }
  }

  public JSONData getList( String name )
  {
    if (table == null) return null;

    try
    {
      JSONArray array = table.getJSONArray( name );
      if (array == null) return null;
      return new JSONData( array );
    }
    catch (JSONException suppress)
    {
      return null;
    }
  }

  public double getReal( String name )
  {
    if (table == null) return 0.0;

    try
    {
      return table.getDouble( name );
    }
    catch (JSONException suppress)
    {
      return 0.0;
    }
  }

  public String getString( int index )
  {
    if (list == null) return null;

    try
    {
      return list.getString( index );
    }
    catch (JSONException suppress)
    {
      return null;
    }
  }

  public String getString( String name )
  {
    if (table == null) return null;

    try
    {
      return table.getString( name );
    }
    catch (JSONException suppress)
    {
      return null;
    }
  }

  public JSONData getTable( int index )
  {
    if (list == null) return null;

    try
    {
      JSONObject object = list.getJSONObject( index );
      if (object == null) return null;
      return new JSONData( object );
    }
    catch (JSONException suppress)
    {
      return null;
    }
  }

  public JSONData getTable( String name )
  {
    if (table == null) return null;

    try
    {
      JSONObject object = table.getJSONObject( name );
      if (object == null) return null;
      return new JSONData( object );
    }
    catch (JSONException suppress)
    {
      return null;
    }
  }

  public JSONData set( String name, boolean value )
  {
    try
    {
      if (table != null) table.put( name, value );
    }
    catch (JSONException ignore)
    {
    }
    return this;
  }

  public JSONData set( String name, double value )
  {
    try
    {
      if (table != null) table.put( name, value );
    }
    catch (JSONException ignore)
    {
    }
    return this;
  }

  public JSONData set( String name, int value )
  {
    try
    {
      if (table != null) table.put( name, value );
    }
    catch (JSONException ignore)
    {
    }
    return this;
  }

  public JSONData set( String name, JSONData value )
  {
    try
    {
      if (table != null)
      {
        if (value.table != null)     table.put( name, value.table );
        else if (value.list != null) table.put( name, value.list );
      }
    }
    catch (JSONException ignore)
    {
    }
    return this;
  }

  public JSONData set( String name, String value )
  {
    try
    {
      if (table != null) table.put( name, value );
    }
    catch (JSONException ignore)
    {
    }
    return this;
  }

  public boolean stringEquals( String key, String other )
  {
    String value = getString( key );

    if (value == null) return (other == null);
    if (other == null) return false;

    return value.equals( other );
  }

  public JSONArray toJSONArray()
  {
    return list;
  }

  public JSONObject toJSONObject()
  {
    return table;
  }

  public String toString()
  {
    if (table != null) return table.toString();
    if (list != null)  return list.toString();
    return "null";
  }

  static public Map<String,Object> json_object_to_map( JSONObject object )
  {
    Map<String,Object> result = new HashMap<>();
    Iterator<String> keys = object.keys();
    while (keys.hasNext())
    {
      String key = keys.next();
      Object value = object.opt( key ); // opt() avoids JSONException
      result.put(key, value);
    }
    return result;
  }

  static public JSONObject map_to_json_object( Object object )
  {
    if (object instanceof Map) return map_to_json_object( (Map<String,Object>) object );
    else                       return new JSONObject();
  }

  static public JSONObject map_to_json_object( Map<String,Object> map )
  {
    JSONObject result = new JSONObject();
    for (Map.Entry<String, Object> entry : map.entrySet())
    {
      String key = entry.getKey();
      Object value = entry.getValue();
      try
      {
        if (value instanceof Map)
        {
          result.put( key, map_to_json_object( (Map<String,Object>) value ) );
        }
        else if (value instanceof HashMap[])
        {
          JSONArray array = new JSONArray();
          for (Map<String,Object> item : (HashMap<String,Object>[])value )
          {
            array.put( map_to_json_object(item) );
          }
          result.put( key, array );
        }
        else
        {
          result.put( key, value );
        }
      }
      catch (JSONException ignore)
      {
      }
    }
    return result;
  }
}
