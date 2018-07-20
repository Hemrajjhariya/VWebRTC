@import WebRTC;
#import <Foundation/Foundation.h>
#import "RTCSessionDescription+JSON.h"

typedef NS_ENUM(NSInteger, VCXSignalingMessageType) {
    kVCXSignalingMessageTypeCandidate,
    kVCXSignalingMessageTypeOffer,
    kVCXSignalingMessageTypeAnswer,
    kVCXSignalingMessageTypeBye,
    kVCXSignalingMessageTypeReady,
	kVCXSignalingMessageTypeTimeout,
	kVCXSignalingMessageTypeFailed,
	kVCXSignalingMessageTypeStarted,
	kVCXSignalingMessageTypeBandwidthAlert,
	kVCXSignalingMessageTypeDataStream,
    kVCXSignalingMessageTypeInitializing,
	kVCXSignalingMessageTypeUpdateAttribute
};

@interface VCXSignalingMessage : NSObject

- (instancetype)initWithStreamId:(id)streamId peerSocketId:(NSString *)peerSocketId;

@property(nonatomic, readonly) VCXSignalingMessageType type;
@property(readonly) NSString *streamId;
@property(readonly) NSString *peerSocketId;

+ (VCXSignalingMessage *)messageFromDictionary:(NSDictionary *)dictionary;
- (NSData *)JSONData;

@end

@interface VCXICECandidateMessage : VCXSignalingMessage

@property(nonatomic, readonly) RTCIceCandidate *candidate;

- (instancetype)initWithCandidate:(RTCIceCandidate *)candidate
                         streamId:(NSString *)streamId
                     peerSocketId:(NSString *)peerSocketId;

@end

@interface VCXSessionDescriptionMessage : VCXSignalingMessage

@property(nonatomic, readonly) RTCSessionDescription *sessionDescription;

- (instancetype)initWithDescription:(RTCSessionDescription *)description
                        streamId:(NSString *)streamId
                       peerSocketId:(NSString *)peerSocketId;

@end

@interface VCXByeMessage : VCXSignalingMessage
@end

@interface VCXReadyMessage : VCXSignalingMessage
@end

@interface VCXTimeoutMessage : VCXSignalingMessage
@end

@interface VCXFailedMessage : VCXSignalingMessage
@end

@interface VCXInitializingMessage : VCXSignalingMessage

@property NSString *agentId;

- (instancetype)initWithStreamId:(NSString *)streamId agentId:(NSString *)agentId;

@end

@interface VCXStartedMessage : VCXSignalingMessage
@end

@interface VCXBandwidthAlertMessage : VCXSignalingMessage
@end

@interface VCXDataStreamMessage : VCXSignalingMessage

@property(nonatomic, strong) NSDictionary* data;

- (instancetype)initWithStreamId:(id)streamId withData:(NSDictionary*) data;

@end

@interface VCXUpdateAttributeMessage : VCXSignalingMessage

@property(nonatomic, strong) NSDictionary* attribute;

- (instancetype)initWithStreamId:(id)streamId withAttribute:(NSDictionary*) attribute;

@end
