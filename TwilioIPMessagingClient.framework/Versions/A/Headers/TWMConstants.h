//
//  TWMConstants.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2011-2016 Twilio. All rights reserved.
//

#import "TWMResult.h"

@class TWMChannels;
@class TWMChannel;
@class TWMMessage;

/** Client connection state. */
typedef NS_ENUM(NSInteger, TWMClientConnectionState) {
    TWMClientConnectionStateUnknown,        ///< Client connection state is not yet known.
    TWMClientConnectionStateDisconnected,   ///< Client is offline and no connection attempt in process.
    TWMClientConnectionStateConnected,      ///< Client is online and ready.
    TWMClientConnectionStateConnecting,     ///< Client is offline and connection attempt is in process.
    TWMClientConnectionStateDenied,         ///< Client connection is denied because of invalid token.
    TWMClientConnectionStateError           ///< Client connection is in the erroneous state.
};

/** Synchronization strategy to use during client initialization. */
typedef NS_ENUM(NSInteger, TWMClientSynchronizationStrategy) {
    TWMClientSynchronizationStrategyAll,              ///< Initialize channels list, members and messages collections for all joined channels.  Loads the number of messages per channel indicated during client initialization.
    TWMClientSynchronizationStrategyChannelsList      ///< Initialize just the channels list, no additional data on channels regardless of join state.  As channels are manually synchronized, the number of messages declared during client initialization will be loaded.
};

/** The synchronization status of the client. */
typedef NS_ENUM(NSInteger, TWMClientSynchronizationStatus) {
    TWMClientSynchronizationStatusStarted = 0,               ///< Client synchronization has started.
    TWMClientSynchronizationStatusChannelsListCompleted,     ///< Channels list is available.
    TWMClientSynchronizationStatusCompleted,                 ///< All joined channels, their members and the requested number of messages are synchronized.
    TWMClientSynchronizationStatusFailed                     ///< Synchronization failed.
};

/** Enumeration indicating the client's logging level. */
typedef NS_ENUM(NSInteger, TWMLogLevel) {
    TWMLogLevelFatal = 0,        ///< Show fatal errors only.
    TWMLogLevelCritical,         ///< Show critical log messages as well as all Fatal log messages.
    TWMLogLevelWarning,          ///< Show warnings as well as all Critical log messages.
    TWMLogLevelInfo,             ///< Show informational messages as well as all Warning log messages.
    TWMLogLevelDebug             ///< Show low-level debugging messages as well as all Info log messages.
};

/** Enumeration indicating the channel's current synchronization status with the server. */
typedef NS_ENUM(NSInteger, TWMChannelSynchronizationStatus) {
    TWMChannelSynchronizationStatusNone = 0,        ///< Channel not ready yet, local object only.
    TWMChannelSynchronizationStatusIdentifier,      ///< Channel SID is available.
    TWMChannelSynchronizationStatusMetadata,        ///< Channel SID, Friendly Name, Attributes and Unique Name are available.
    TWMChannelSynchronizationStatusAll,             ///< Channels, Members and Messages collections are ready to use.
    TWMChannelSynchronizationStatusFailed           ///< Channel synchronization failed.
};

/** Enumeration indicating the user's current status on a given channel. */
typedef NS_ENUM(NSInteger, TWMChannelStatus) {
    TWMChannelStatusInvited = 0,        ///< User is invited to the channel but not joined.
    TWMChannelStatusJoined,             ///< User is joined to the channel.
    TWMChannelStatusNotParticipating    ///< User is not participating on this channel.
};

/** Enumeration indicating the channel's visibility. */
typedef NS_ENUM(NSInteger, TWMChannelType) {
    TWMChannelTypePublic = 0,        ///< Channel is publicly visible
    TWMChannelTypePrivate            ///< Channel is private and only visible to invited members.
};

/** Enumeration indicating the updates made to the TWMUserInfo object. */
typedef NS_ENUM(NSInteger, TWMUserInfoUpdate) {
    TWMUserInfoUpdateFriendlyName = 0,        ///< The friendly name changed.
    TWMUserInfoUpdateAttributes,              ///< The attributes changed.
    TWMUserInfoUpdateReachabilityOnline,      ///< The user's online status changed.
    TWMUserInfoUpdateReachabilityNotifiable   ///< The user's notifiability status changed.
};

/** Completion block which will indicate the TWMResult of the operation. */
typedef void (^TWMCompletion)(TWMResult *result);

/** Completion block which will indicate the TWMResult of the operation and a channels object. */
typedef void (^TWMChannelListCompletion)(TWMResult *result, TWMChannels *channelsList);

/** Completion block which will indicate the TWMResult of the operation and a channel. */
typedef void (^TWMChannelCompletion)(TWMResult *result, TWMChannel *channel);

/** Completion block which will indicate the TWMResult of the operation and a list of messages. */
typedef void (^TWMMessagesCompletion)(TWMResult *result, NSArray<TWMMessage *> *messages);

/** Channel creation options key for setting friendly name. */
FOUNDATION_EXPORT NSString *const TWMChannelOptionFriendlyName;

/** Channel creation options key for setting unqiue name. */
FOUNDATION_EXPORT NSString *const TWMChannelOptionUniqueName;

/** Channel creation options key for setting type.  Expected values are @(TWMChannelTypePublic) or @(TWMChannelTypePrivate) */
FOUNDATION_EXPORT NSString *const TWMChannelOptionType;

/** Channel creation options key for setting attributes.  Expected value is an NSDictionary* */
FOUNDATION_EXPORT NSString *const TWMChannelOptionAttributes;

/** The Twilio IP Messaging error domain used as NSError's 'domain'. */
FOUNDATION_EXPORT NSString *const TWMErrorDomain;

/** The errorCode specified when an error client side occurs without another specific error code. */
FOUNDATION_EXPORT NSInteger const TWMErrorGeneric;

/** The userInfo key for the error message, if any. */
FOUNDATION_EXPORT NSString *const TWMErrorMsgKey;
