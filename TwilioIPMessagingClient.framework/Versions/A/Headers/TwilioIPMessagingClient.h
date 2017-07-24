//
//  TwilioIPMessagingClient.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2011-2016 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioCommon/TwilioCommon.h>

#import "TWMConstants.h"
#import "TWMError.h"
#import "TWMChannels.h"
#import "TWMChannel.h"
#import "TWMMessages.h"
#import "TWMMessage.h"
#import "TWMMember.h"
#import "TWMUserInfo.h"

@class TwilioIPMessagingClientProperties;
@protocol TwilioIPMessagingClientDelegate;

/** Represents an IP Messaging client connection to Twilio. */
@interface TwilioIPMessagingClient : NSObject

/** Access manager to use with this client. */
@property (nonatomic, strong) TwilioAccessManager *accessManager;

/** Messaging client delegate */
@property (nonatomic, weak) id<TwilioIPMessagingClientDelegate> delegate;

/** The info for the logged in user in the IP Messaging system. */
@property (nonatomic, strong, readonly) TWMUserInfo *userInfo;

/** The client's current connection state. */
@property (nonatomic, assign, readonly) TWMClientConnectionState connectionState;

/** The current client synchronization state. */
@property (nonatomic, assign, readonly) TWMClientSynchronizationStatus synchronizationStatus;

/** Sets the logging level for the client. 
 
 @param logLevel The new log level.
 */
+ (void)setLogLevel:(TWMLogLevel)logLevel;

/** The logging level for the client. 
 
 @return The log level.
 */
+ (TWMLogLevel)logLevel;

/** Initialize a new IP Messaging client instance with a token manager.
 
 @param accessManager Instance of TwilioAccessManager.
 @param properties The properties to initialize the client with, if this is nil defaults will be used.
 @param delegate Delegate conforming to TwilioIPMessagingClientDelegate for IP Messaging client lifecycle notifications.
 
 @return New IP Messaging client instance.
 */
+ (TwilioIPMessagingClient *)ipMessagingClientWithAccessManager:(TwilioAccessManager *)accessManager
                                                     properties:(TwilioIPMessagingClientProperties *)properties
                                                       delegate:(id<TwilioIPMessagingClientDelegate>)delegate;

/** Returns the version of the SDK
 
 @return The IP Messaging client version.
 */
- (NSString *)version;

/** List of channels available to the current user.
 
 This will be nil until the client is fully initialized, see the client delegate callback `ipMessagingClient:updated:`
 
 @return The channelsList object.
 */
- (TWMChannels *)channelsList;

/** Register APNS token for push notification updates.
 
 @param token The APNS token which usually comes from 'didRegisterForRemoteNotificationsWithDeviceToken'.
 */
- (void)registerWithToken:(NSData *)token;

/** De-register from push notification updates.
 
 @param token The APNS token which usually comes from 'didRegisterForRemoteNotificationsWithDeviceToken'.
 */
- (void)deregisterWithToken:(NSData *)token;

/** Queue the incoming notification with the messaging library for processing - notifications usually arrive from 'didReceiveRemoteNotification'.
 
 @param notification The incomming notification.
 */
- (void)handleNotification:(NSDictionary *)notification;

/** Indicates whether reachability is enabled for this instance.
 
 @return YES if reachability is enabled.
 */
- (BOOL)isReachabilityEnabled;

/** Cleanly shut down the messaging subsystem when you are done with it. */
- (void)shutdown;

@end

#pragma mark -

@interface TwilioIPMessagingClientProperties : NSObject

/** The syncrhonization strategy to use during client initialization.  Default: TWMClientSynchronizationStrategyChannelsList
 @see TWMClientSynchronizationStrategy */
@property (nonatomic, assign) TWMClientSynchronizationStrategy synchronizationStrategy;

/** The number of most recent messages to fetch automatically when synchronizing a channel.  Default: 100 */
@property (nonatomic, assign) uint initialMessageCount;

@property (nonatomic, copy) NSString *region;

@end

#pragma mark -

/** This protocol declares the IP Messaging client delegate methods. */
@protocol TwilioIPMessagingClientDelegate <NSObject>
@optional

/** Called when the client connection state changes.
 
 @param client The IP Messaging client.
 @param state The current connection state of the client.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client connectionStateChanged:(TWMClientConnectionState)state;

/** Called when the client synchronization state changes during startup.
 
 @param client The IP Messaging client.
 @param status The current synchronization status of the client.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client synchronizationStatusChanged:(TWMClientSynchronizationStatus)status;

/** Called when the current user has a channel added to their channel list.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelAdded:(TWMChannel *)channel;

/** Called when one of the current users channels is changed.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelChanged:(TWMChannel *)channel;

/** Called when one of the current users channels is deleted.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelDeleted:(TWMChannel *)channel;

/** Called when a channel the current the client is aware of changes synchronization state.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param status The current synchronization status of the channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel synchronizationStatusChanged:(TWMChannelSynchronizationStatus)status;

/** Called when a channel the current user is subscribed to has a new member join.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel memberJoined:(TWMMember *)member;

/** Called when a channel the current user is subscribed to has a member modified.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel memberChanged:(TWMMember *)member;

/** Called when a channel the current user is subscribed to has a member leave.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel memberLeft:(TWMMember *)member;

/** Called when a channel the current user is subscribed to receives a new message.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param message The message.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel messageAdded:(TWMMessage *)message;

/** Called when a message on a channel the current user is subscribed to is modified.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param message The message.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel messageChanged:(TWMMessage *)message;

/** Called when a message on a channel the current user is subscribed to is deleted.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param message The message.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TWMChannel *)channel messageDeleted:(TWMMessage *)message;

/** Called when an error occurs.
 
 @param client The IP Messaging client.
 @param error The error.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client errorReceived:(TWMError *)error;

/** Called when a member of a channel starts typing.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client typingStartedOnChannel:(TWMChannel *)channel member:(TWMMember *)member;

/** Called when a member of a channel ends typing.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client typingEndedOnChannel:(TWMChannel *)channel member:(TWMMember *)member;

/** Called when you are successfully registered for push notifications. 
 
 @param client The IP Messaging client.
 */
- (void)ipMessagingClientToastSubscribed:(TwilioIPMessagingClient *)client;

/** Called as a result of TwilioIPMessagingClient's receivedNotification: method being invoked.  receivedNotification: parses the push payload and extracts the channel and message for the push notification then calls this delegate method. 
 
 @param client The IP Messaging client.
 @param channel The channel for the push notification.
 @param message The message for the push notification.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client toastReceivedOnChannel:(TWMChannel *)channel message:(TWMMessage *)message;

/** Called when registering for push notifications fails.
 
 @param client The IP Messaging client.
 @param error An error indicating the failure.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client toastRegistrationFailedWithError:(TWMError *)error;

/** Called when the current user's or that of any subscribed channel member's userInfo is updated.
 
 @param client The IP Messaging client.
 @param userInfo The userInfo object for changed local user or channel member.
 @param updated Indicates what portion of the object changed.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client userInfo:(TWMUserInfo *)userInfo updated:(TWMUserInfoUpdate)updated;

@end
