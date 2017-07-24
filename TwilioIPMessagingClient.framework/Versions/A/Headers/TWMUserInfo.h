//
//  TWMUserInfo.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2011-2016 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TWMConstants.h"

/** User information for the current user and other channel members. */
@interface TWMUserInfo : NSObject

/** The identity for this user. */
@property (nonatomic, copy, readonly) NSString *identity;

/** The friendly name for this user. */
@property (nonatomic, copy, readonly) NSString *friendlyName;

/** Return this user's attributes.
 
 @return The developer-defined extensible attributes for this user.
 */
- (NSDictionary<NSString *, id> *)attributes;

/** Set this user's attributes.
 
 @param attributes The new developer-defined extensible attributes for this user. (Supported types are NSString, NSNumber, NSArray, NSDictionary and NSNull)
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setAttributes:(NSDictionary<NSString *, id> *)attributes
           completion:(TWMCompletion)completion;

/** Set this user's friendly name.
 
 @param friendlyName The new friendly name for this user.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setFriendlyName:(NSString *)friendlyName
             completion:(TWMCompletion)completion;

/** Indicates whether the user is online.  Note that if TwilioIPMessagingClient indicates reachability is not enabled, this will return NO.
 
 @return YES if the user is online.
 */
- (BOOL)isOnline;

/** Indicates whether the user is notifiable.  Note that if TwilioIPMessagingClient indicates reachability is not enabled, this will return NO.
 
 @return YES if the user is notifiable.
 */
- (BOOL)isNotifiable;

@end
