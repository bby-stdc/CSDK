//
//  TWMMessages.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2011-2016 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TWMConstants.h"
#import "TWMMessage.h"

/** Representation of an IP Messaging channel's message list. */
@interface TWMMessages : NSObject

/** Index of the last Message the User has consumed in this Channel. */
@property (nonatomic, copy, readonly) NSNumber *lastConsumedMessageIndex;

/** Creates a place-holder message which can be populated and sent with sendMessage:completion:

 @param body Body for new message.
 @return Place-holder TWMMessage instance
 */
- (TWMMessage *)createMessageWithBody:(NSString *)body;

/** Sends a message to the channel.
 
 @param message The message to send.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)sendMessage:(TWMMessage *)message
         completion:(TWMCompletion)completion;

/** Removes the specified message from the channel.
 
 @param message The message to remove.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeMessage:(TWMMessage *)message
           completion:(TWMCompletion)completion;

/** Returns messages received so far from backend, messages are loaded asynchronously so this may not fully represent all history available for channel.
 
 @return Messages received by IP Messaging Client so far for the given channel.
 @deprecated Please use the asynchronous get messages methods instead.
 */
- (NSArray<TWMMessage *> *)allObjects DEPRECATED_MSG_ATTRIBUTE("Please use the asynchronous get messages methods instead");

/** Fetches the most recent <count> messages.  This will return locally cached messages if they are all available or may require a load from the server.
 
 @param count The number of most recent messages to return.
 @param completion Completion block that will specify the result of the operation as well as the requested messages if successful.
 */
- (void)getLastMessagesWithCount:(NSUInteger)count completion:(TWMMessagesCompletion)completion;

/** Fetches at most <count> messages including and prior to the specified <index>.  This will return locally cached messages if they are all available or may require a load from the server.

 @param index The starting point for the request.
 @param count The number of preceeding messages to return.
 @param completion Completion block that will specify the result of the operation as well as the requested messages if successful.
 */
- (void)getMessagesBefore:(NSUInteger)index withCount:(NSUInteger)count completion:(TWMMessagesCompletion)completion;

/** Fetches at most <count> messages inclulding and subsequent to the specified <index>.  This will return locally cached messages if they are all available or may require a load from the server.
 
 @param index The starting point for the request.
 @param count The number of succeeding messages to return.
 @param completion Completion block that will specify the result of the operation as well as the requested messages if successful.
 */
- (void)getMessagesAfter:(NSUInteger)index withCount:(NSUInteger)count completion:(TWMMessagesCompletion)completion;

/** Returns the message with the specified index.
 
 @param index The index of the message.
 @return The requested message or nil if no such message exists.
 */
- (TWMMessage *)messageWithIndex:(NSNumber *)index;

/** Returns the oldest message starting at index.  If the message at index exists, it will be returned otherwise the next oldest message that presently exists will be returned.
 
 @param index The index of the last message reported as read (may refer to a deleted message).
 @return Message at or prior to the specified index.
 */
- (TWMMessage *)messageForConsumptionIndex:(NSNumber *)index;

/** Set the last consumed index for this Member and Channel.  Allows you to set any value, including smaller than the current index.
 
 @param index The new index.
 */
- (void)setLastConsumedMessageIndex:(NSNumber *)index;

/** Update the last consumed index for this Member and Channel.  Only update the index if the value specified is larger than the previous value.
 
 @param index The new index.
 */
- (void)advanceLastConsumedMessageIndex:(NSNumber *)index;

/** Update the last consumed index for this Member and Channel to the max message currently on this device.
 */
- (void)setAllMessagesConsumed;

/** Reset the last consumed index for this Member and Channel to no messages consumed.
 */
- (void)setNoMessagesConsumed;

@end
