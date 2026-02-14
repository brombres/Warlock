package com.developer.appname;

import android.content.*;
import android.content.pm.*;
import android.os.*;
import android.util.Log;
import java.util.*;
import org.json.*;
import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity
{
  static public MainActivity instance;

  public HashMap<String,MessageHandler> message_handlers = new HashMap<String,MessageHandler>();
  public ArrayList<ActivityResult> pending_activity_results = new ArrayList<ActivityResult>();

  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate( savedInstanceState );

    instance = this;

    Log.d( "Warlock", "Launching app version " + getVersionName() + " (" + getVersionCode() + ")" );

    // Add additional configuration here
    BackendlessInterface.configure( this );
    FacebookInterface.configure( this );
    GoogleSignInInterface.configure( this );
    UnityAdsInterface.configure( this );

    onMessage( "AppStore.configure", m -> { AppStoreInterface.configure( this, List.of("ts_premium") ); } );

    onMessage( "MainActivity.tick", m -> {tick();} );

    // EXAMPLE
    //onMessage(
    //  "marco",
    //  new MessageHandler()
    //  {
    //    public JSONData on( Message m ) throws JSONException
    //    {
    //      return new JSONData().set( "result", "polo" );
    //    }
    //  }
    //);
  }

  @Override
  public void onActivityResult( int requestCode, int resultCode, Intent data )
  {
    super.onActivityResult( requestCode, resultCode, data );
    pending_activity_results.add( new ActivityResult(requestCode,resultCode,data) );
  }

  // Called from the Rogue layer.
  public void tick()
  {
    for (ActivityResult result : pending_activity_results)
    {
      FacebookInterface.callback_manager.onActivityResult( result.request_code, result.result_code, result.data );
    }
    pending_activity_results.clear();
  }

  @Override
  protected String[] getLibraries()
  {
    // Order matters: SDL3 first, then the game library
    return new String[] {
      "SDL3",
        "warlock"  // name of the C++ shared lib
    };
  }

  @Override
  protected String getMainFunction()
  {
    // SDLActivity will call this function in native code
    return "SDL_main";
  }

  public void onMessage( String id, MessageHandler handler )
  {
    message_handlers.put( id, handler );
  }

  public void receiveMessage( String message )
  {
    Message m = new Message( new JSONData(message) );
    MessageHandler handler = message_handlers.get( m.id );

    if (handler != null)
    {
      runOnUiThread( () -> {
        handler.on( m );
      } );
    }
    else
    {
      Log.d( "Warlock", "No message handler for " + m.id );
    }
  }

  static public void sendMessage( Message message )
  {
    sendMessage( (message != null) ? message.toString() : null );
  }

  native static public void sendMessage( String message );

  //----------------------------------------------------------------------------

  public String getVersionName()
  {
    try {
      PackageManager pm = this.getPackageManager();
      PackageInfo pi = pm.getPackageInfo(this.getPackageName(), 0);
      return pi.versionName;   // e.g. "1.2.3"
    } catch (PackageManager.NameNotFoundException e) {
      return "unknown";
    }
  }

  public long getVersionCode()
  {
    try {
      PackageManager pm = this.getPackageManager();
      PackageInfo pi = pm.getPackageInfo(this.getPackageName(), 0);

      // Android 9+ (API 28+)
      if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.P) {
        return pi.getLongVersionCode();
      } else {
        // Deprecated but required for older devices
        return pi.versionCode;
      }
    } catch (PackageManager.NameNotFoundException e) {
      return -1;
    }
  }

  class ActivityResult
  {
    int    request_code, result_code;
    Intent data;

    public ActivityResult( int request_code, int result_code, Intent data )
    {
      this.request_code = request_code;
      this.result_code  = result_code;
      this.data = data;
    }
  }
}
