@import WebRTC;
#import <Foundation/Foundation.h>
#import "VCXLogger.h"
#import "VCXSignalingChannel.h"
#import "VCXClientDelegate.h"
#import "VCXClientState.h"

typedef RTCSessionDescription * (^SDPHackCallback)(RTCSessionDescription *description);

static SDPHackCallback sdpHackCallback;
static NSString *preferredVideoCodec;
static NSString *defaultVideoCodec = @"VP8";
static NSString *const kVCXAppClientErrorDomain = @"ECAppClient";
static NSInteger const kVCXAppClientErrorCreateSDP = -3;
static NSInteger const kVCXAppClientErrorSetSDP = -4;
static int const kKbpsMultiplier = 1000;

/**
 Returns *VCXClientState* stringified.
 
 @param state VCXClientState.
 
 @return NSString*
 */
extern NSString* clientStateToString(VCXClientState state);

@class VCXClient;

///-----------------------------------
/// @name VCXClient Interface
///-----------------------------------

@interface VCXClient : NSObject <VCXSignalingChannelDelegate>

///-----------------------------------
/// @name Properties
///-----------------------------------

/// VCXClientDelegate instance.
@property (weak, nonatomic) id<VCXClientDelegate> delegate;
/// Server configuration for this client.
@property (nonatomic, readonly) NSDictionary *serverConfiguration;
/// Local Stream assigned to this client.
@property (strong, nonatomic) RTCMediaStream *localStream;
/// Max bitrate allowed for this client to use.
@property NSNumber *maxBitrate;
/// Should bitrate be limited to `maxBitrate` value?
@property BOOL limitBitrate;
/// Peer socket id assigned by VCX for signaling P2P connections.
@property NSString *peerSocketId;
/// The streamId
@property NSString *streamId;

///-----------------------------------
/// @name Initializers
///-----------------------------------

- (instancetype)initWithDelegate:(id<VCXClientDelegate>)delegate;
- (instancetype)initWithDelegate:(id<VCXClientDelegate>)delegate
                  andPeerFactory:(RTCPeerConnectionFactory *)peerFactory;
- (instancetype)initWithDelegate:(id<VCXClientDelegate>)delegate
                     peerFactory:(RTCPeerConnectionFactory *)peerFactory
                    peerSocketId:(NSString *)peerSocketId;
- (instancetype)initWithDelegate:(id<VCXClientDelegate>)delegate
                     peerFactory:(RTCPeerConnectionFactory *)peerFactory
                        streamId:(NSString *)streamId
                    peerSocketId:(NSString *)peerSocketId;
///-----------------------------------
/// @name Instance Methods
///-----------------------------------

- (void)disconnect;

///-----------------------------------
/// @name Class Methods
///-----------------------------------

+ (void)setPreferredVideoCodec:(NSString *)codec;
+ (NSString *)getPreferredVideoCodec;
+ (void)hackSDPWithBlock:(SDPHackCallback)callback;

@end
