#import <Foundation/Foundation.h>

///-----------------------------------
/// @name Dictionary Keys
///-----------------------------------
static NSString *const kEventKeyId                  = @"id";
static NSString *const kEventKeyStreamId            = @"streamId";
static NSString *const kEventKeyPeerSocketId        = @"peerSocket";
static NSString *const kEventKeyAudio               = @"audio";
static NSString *const kEventKeyData                = @"data";
static NSString *const kEventKeyVideo               = @"video";
static NSString *const kEventKeyAttributes          = @"attributes";
static NSString *const kEventKeyUpdatedAttributes   = @"attrs";
static NSString *const kEventKeyDataStream          = @"msg";

///-----------------------------------
/// @name VCX Event Types
///-----------------------------------
static NSString * const kEventOnAddStream				= @"onAddStream";
static NSString * const kEventOnRemoveStream			= @"onRemoveStream";
static NSString * const kEventSignalingMessageVCX		= @"media_engine_connecting";
static NSString * const kEventSignalingMessagePeer		= @"signaling_message_peer";
static NSString * const kEventPublishMe					= @"publish_me";
static NSString * const kEventOnDataStream				= @"onDataStream";
static NSString * const kEventOnUpdateAttributeStream	= @"onUpdateAttributeStream";


static NSString * const kEventOnConnect = @"connect";
static NSString * const kEventOnDisconnect = @"disconnect";
static NSString * const kEventOnConnectError = @"onConnectError";
static NSString * const kEventOnTimeOutError = @"onTimeOutError";
static NSString * const kEventOnSubscribeP2P = @"onSubscribeP2P";
static NSString * const kEventOnPublishP2P = @"onPublishP2P";
static NSString * const kEventOnSubscribe = @"subscribe";
static NSString * const kEventOnPublish = @"publish";
static NSString * const kEventOnRemoveTrack = @"onRemoveTrack";
static NSString * const kEventOnUnpublishme = @"unpublish_me";
static NSString * const kEventOnBandwidthAlert = @"onBandwidthAlert";
static NSString * const kEventOnConnectionFailed = @"connection_failed";
static NSString * const kEventOnError = @"error";
static NSString * const kEventOnReconnecting = @"reconnecting";
static NSString * const kEventOnReconnect = @"reconnect";
static NSString * const kEventOnReconnected = @"reconnected";
static NSString * const kEventOnReconnectAttempt = @"reconnect_attempt";
static NSString * const kEventOnReconnectError = @"reconnect_error";
static NSString * const kEventOnReconnectFailed = @"reconnect_failed";
static NSString * const kEventOnUserConnected = @"user-connected";
static NSString * const kEventOnUserDisconnected = @"user-disconnected";
static NSString * const kEventOnUserSubscribed = @"user-subscribed";
static NSString * const kEventOnUserUnsubscribed = @"user-unsubscribed";

/**
 @interface VCXSignalingEvent
 */
@interface VCXSignalingEvent : NSObject

@property NSString *name;
@property NSDictionary *message;
@property NSString *streamId;
@property NSString *peerSocketId;
@property NSDictionary *attributes;
@property NSDictionary *updatedAttributes;
@property NSDictionary *dataStream;
@property BOOL audio;
@property BOOL video;
@property BOOL data;

- (instancetype)initWithName:(NSString *)name
                     message:(NSDictionary *)message;
@end
