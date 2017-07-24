//
//  TWMMessage.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2011-2016 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TWMConstants.h"

/** Representation of a Message on an IP Messaging channel. */
@interface TWMMessage : NSObject

/** The unique identifier for this message. */
@property (nonatomic, copy, readonly) NSString *sid;

/** Index of Message in the Channel's messages stream. */
@property (nonatomic, copy, readonly) NSNumber *index;

/** The identity of the author of the message. */
@property (nonatomic, copy, readonly) NSString *author;

/** The body of the message. */
@property (nonatomic, copy, readonly) NSString *body;

/** The timestamp of the message. */
@property (nonatomic, copy, readonly) NSString *timestamp;

/** The timestamp of the message as an NSDate. */
@property (nonatomic, strong, readonly) NSDate *timestampAsDate;

/** The timestamp the message was last updated. */
@property (nonatomic, copy, readonly) NSString *dateUpdated;

/** The timestamp the message was last updated as an NSDate. */
@property (nonatomic, strong, readonly) NSDate *dateUpdatedAsDate;

/** Who the the message was last updated by. */
@property (nonatomic, copy, readonly) NSString *lastUpdatedBy;

/** Update the body of this message
 
 @param body The new body for this message.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)updateBody:(NSString *)body completion:(TWMCompletion)completion;

/** Return this message's attributes.
 
 @return The developer-defined extensible attributes for this message.
 */
- (NSDictionary<NSString *, id> *)attributes;

/** Set this message's attributes.
 
 @param attributes The new developer-defined extensible attributes for this message. (Supported types are NSString, NSNumber, NSArray, NSDictionary and NSNull)
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setAttributes:(NSDictionary<NSString *, id> *)attributes
           completion:(TWMCompletion)completion;

@end
