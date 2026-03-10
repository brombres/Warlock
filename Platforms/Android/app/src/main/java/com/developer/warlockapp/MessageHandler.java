package com.developer.warlockapp;

import org.json.*;

public interface MessageHandler
{
  abstract public void on( Message message );
}
