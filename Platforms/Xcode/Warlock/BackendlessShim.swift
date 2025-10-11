//
//  BackendlessShim.swift
//  Warlock
//
//  Add this to your Xcode project & uncomment Backendless lines in Podfile
//  to enable Backendless support.
//
//  Created by Abe Pralle on 9/25/25.


import Foundation
import Backendless

@objc class BackendlessBridge: NSObject {
  @objc static let shared = BackendlessBridge()

  private let backendless = Backendless.shared

  @objc func initialize( appId:String, apiKey:String)
  {
    backendless.initApp( applicationId:appId, apiKey:apiKey )
    backendless.userService.stayLoggedIn = true;
  }

  @objc func registerUser(
    email:    String,
    password: String,
    completion: @escaping (NSString?,NSString?) -> Void
  )
  {
    let user = BackendlessUser()
    user.email = email
    user.password = password

    backendless.userService.registerUser(
      user:            user,
      responseHandler: { registeredUser in completion(registeredUser.objectId as NSString?, nil) },
      errorHandler:    { fault in completion(nil, fault.message as NSString?) }
    )
  }

  @objc func login(
    email: String,
    password: String,
    completion: @escaping (NSString?, NSString?) -> Void
  )
  {
    backendless.userService.login(
      identity:email,
      password:password,
      responseHandler: { user in completion(user.objectId as NSString?, nil) },
      errorHandler: { fault in completion(nil, fault.message as NSString?) }
    )
  }

  @objc func logout( completion:@escaping (ObjCBool, NSString?) -> Void )
  {
    backendless.userService.logout(
      responseHandler: { completion(true, nil) },
      errorHandler: { fault in completion(false, fault.message as NSString?) }
    )
  }

  @objc func isUserLoggedIn( _ completion: @escaping (ObjCBool) -> Void )
  {
    backendless.userService.isValidUserToken(
      responseHandler: { valid in completion(ObjCBool(valid)) },
      errorHandler: { _ in completion(false) }
    )
  }

  @objc func invokeService(
    serviceName:String,
    method:String,
    parameters:Any?,
    completion:@escaping (NSDictionary?, NSString?) -> Void
  )
  {
    var parameter_dictionary:Any? = nil

    // Detect if the Objective-C side sent a JSON string or a dictionary
    if let dict = parameters as? [String:Any]
    {
      parameter_dictionary = dict
    }
    else if let json_string = parameters as? String,
            let data        = json_string.data( using:.utf8 ),
            let json_object = try? JSONSerialization.jsonObject( with:data )
    {
      parameter_dictionary = json_object
    }

    backendless.customService.invoke(
      serviceName:serviceName,
      method:method,
      parameters:parameter_dictionary,
      responseHandler:
      {
        result in
        if let dict = result as? NSDictionary
        {
          completion( ["data":dict] as NSDictionary, nil )
        }
        else if let array = result as? [Any]
        {
          completion( ["data":array] as NSDictionary, nil )
        }
        else if let value = result
        {
          completion( ["data":value], nil )
        }
        else
        {
          completion( nil, nil )
        }
      },
      errorHandler: { fault in completion(nil, fault.message as NSString?) }
    )
  }

}
