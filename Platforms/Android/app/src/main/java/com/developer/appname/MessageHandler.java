package com.developer.appname;

import org.json.*;

public interface MessageHandler
{
  abstract public void on( Message message );
}
